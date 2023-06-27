/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/06/27 18:21:48 by bastien          ###   ########.fr       */
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
	if (shell->error || !str_piped[0])
	{
		ft_free_tab(str_piped);
		return ;
	}
	if (word_exist(str_piped[0]))
	{
		shell->cmd = ft_fill_cmd(str_piped[(*i)++], shell, parsing);
		if (!shell->cmd)
		{
			ft_free_tab(str_piped);
			return ;
		}
	}
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
				tmp = tmp->next;
			}
			else
				tmp = ft_fill_cmd(str_piped[i], shell, parsing);
			if (!tmp && !tmp->next)
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


/*static void	split_in_cmd(char **str_piped, t_shell *shell, t_parsing *parsing)
{
	int			i;
	t_cmd		*tmp;

	i = 0;
	i = 0;
	if (shell->error || !str_piped[0])
	{
		ft_free_tab(str_piped);
		return ;
	}
	shell->cmd = ft_fill_cmd(str_piped[i++], shell, parsing);
	if (!shell->cmd)
	{
		ft_free_tab(str_piped);
		return ;
	}
	tmp = shell->cmd;
	if (tmp->infile == -2)
		tmp->infile = 0;
	while (str_piped[i])
	{
		tmp->next = ft_fill_cmd(str_piped[i], shell, parsing);
		if (!tmp->next)
		{
			ft_clear_cmd(shell->cmd);
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	if (tmp->outfile == -2)
		tmp->outfile = 1;
	ft_free_tab(str_piped);
}*/

int	ft_parsing(t_shell *shell, char *str)
{
	t_parsing	parsing;

	add_history(str);
	parsing.quote = NULL;
	ft_cut_quote_space(str, &parsing, shell);
	split_in_cmd(ft_split(str, '|'), shell, &parsing);
	free(str);
	if (!shell->cmd)
		return (-1);
	if (shell->last_error)
		shell->last_error = WEXITSTATUS(shell->last_error);
	return (0);
}
