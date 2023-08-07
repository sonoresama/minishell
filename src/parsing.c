/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/08/07 18:33:35 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_exist(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

static void	first_occur(char **str_piped, t_shell *shell, t_parsing *parsing, int *i)
{
	if (shell->error || !str_piped || !str_piped[0])
	{
		ft_free_tab(str_piped);
		return ;
	}
	if (word_exist(str_piped[0]))
		shell->cmd = ft_fill_cmd(str_piped[(*i)++], shell, parsing);
	else
		(*i)++;
}

static void	split_in_cmd(char **str_piped, t_shell *shell, t_parsing *parsing)
{
	int			i;
	t_cmd		*tmp;

	i = 0;
	first_occur(str_piped, shell, parsing, &i);
	tmp = shell->cmd;
	if (tmp && tmp->infile == -2)
		tmp->infile = 0;
	while (str_piped && str_piped[i])
	{
		if (word_exist(str_piped[i]))
		{
			if (tmp)
			{
				tmp->next = ft_fill_cmd(str_piped[i], shell, parsing);
				if (tmp->next)
					tmp = tmp->next;
			}
			else
			{
				tmp = ft_fill_cmd(str_piped[i], shell, parsing);
				if (shell->error == REDIR_ERROR)
				{
					shell->error = 1;
					tmp->infile = open("/tmp/tmp_minishell", O_CREAT, 0644);
				}
				if (tmp)
					shell->cmd = tmp;
			}
			if ((!tmp || !tmp->next) && shell->error == MALLOC_ERROR)
			{
				ft_clear_cmd(shell->cmd);
				break ;
			}
		}
		i++;
	}
	if (tmp && tmp->outfile == -2)
		tmp->outfile = 1;
	ft_free_tab(str_piped);
}

static int	check_pipe(char *str, char **tab)
{
	int	i;
	int	count;
	int	line_count;

	line_count = 0;
	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	i = 0;
	while (tab && tab[i++])
		line_count++;
	if (count == line_count - 1 || count == 0)
		return (0);
	else
		return (1);
}

void	print_redir(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->heredoc[i])
	{
		printf("heredoc :%s\n", parsing->heredoc[i]);
		i++;
	}
	i = 0;
	while (parsing->redir[i])
	{
		printf("redir :%s\n", parsing->redir[i]);
		i++;
	}
}

int	ft_parsing(t_shell *shell, char *str)
{
	t_parsing	*parsing;
	char	**tab;

	parsing = malloc (sizeof(t_parsing));
	parsing->quote = NULL;
	parsing->dquote = NULL;
	parsing->heredoc = NULL;
	parsing->redir = NULL;
	add_history(str);
	ft_cut_quote_space(str, parsing, shell);
	if (shell->error == SYNTAX_ERROR)
	{	
		ft_clear_parsing(parsing);
		free(str);
		return (-1);
	}
	ft_copy_redir(str, parsing, shell);
	print_redir(parsing);
	replace_var_env_in_str(&str, shell);
	replace_var_env_in_lst(parsing, shell);
	tab = ft_split(str, '|');
	if (check_pipe(str, tab))
	{
		ft_clear_parsing(parsing);
		ft_free_tab(tab);
		free(str);
		return (-1);
	}
	if (!tab || !tab[0])
	{
		ft_clear_parsing(parsing);
		free(str);
		return (0);
	}
	split_in_cmd(tab, shell, parsing);
	ft_clear_parsing(parsing);
	free(str);
	if (!shell->cmd && !shell->error)
		return (-1);
	return (0);
}
