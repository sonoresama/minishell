/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/09/13 13:48:28 by blerouss         ###   ########.fr       */
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

static void	split_cmd_bis(t_cmd **tmp, char *str, t_shell *sh, t_parsing *par)
{
	if ((*tmp))
	{
		(*tmp)->next = ft_fill_cmd(str, sh, par);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	else
	{
		(*tmp) = ft_fill_cmd(str, sh, par);
		if (sh->error == REDIR_ERROR)
		{
			sh->error = 1;
			if ((*tmp))
				(*tmp)->infile = open("/tmp/tmp_minishell", O_CREAT, 0644);
		}
		if ((*tmp))
			sh->cmd = (*tmp);
	}
}

static int	split_in_cmd_bis(t_cmd **t, char *str, t_shell *sh, t_parsing *par)
{
	split_cmd_bis(t, str, sh, par);
	if ((!(*t) || !(*t)->next) && (sh->error == 17 || sh->error == 10))
	{
		ft_clear_cmd(sh->cmd);
		return (1);
	}
	if (!sh->cmd)
	{
		sh->cmd = (*t);
		if ((*t) && (*t)->infile == -2)
			(*t)->infile = 0;
	}
	return (0);
}

static void	split_in_cmd(char **str_piped, t_shell *shell, t_parsing *parsing)
{
	int			i;
	t_cmd		*tmp;

	i = 0;
	tmp = NULL;
	if (shell->error || !str_piped || !str_piped[0])
	{
		ft_free_tab(str_piped);
		return ;
	}
	while (str_piped && str_piped[i])
	{
		if (word_exist(str_piped[i]))
			if (split_in_cmd_bis(&tmp, str_piped[i], shell, parsing))
				break ;
		i++;
	}
	if (tmp && tmp->outfile == -2)
		tmp->outfile = 1;
	ft_free_tab(str_piped);
}

int	ft_parsing(t_shell *shell, char **str, t_parsing **parsing)
{
	char	**tab;

	(*parsing) = ft_fill_parsing((*str), NULL, shell);
	if (shell->error == MALLOC_ERROR)
		return (0);
	add_history((*str));
	if (ft_cut_quote_space((*str), (*parsing), shell) == MALLOC_ERROR)
		return (0);
	if (shell->error == SYNTAX_ERROR)
		return (-1);
	if (ft_copy_redir((*str), (*parsing), shell) || replace_var_env_in_str(str
			, shell) || replace_var_env_in_lst((*parsing), shell))
		return (0);
	tab = ft_split((*str), '|');
	if (tab && check_pipe((*str), tab))
		return (-1);
	if (!tab || !tab[0])
	{
		ft_free_tab(tab);
		return (0);
	}
	split_in_cmd(tab, shell, (*parsing));
	if (!shell->cmd && !shell->error)
		return (-1);
	return (0);
}
