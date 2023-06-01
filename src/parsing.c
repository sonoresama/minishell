/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/06/01 16:45:07 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_My_func	is_built_in(char *str)
{
	if (!ft_strncmp(str, "exit", 4))
		return (&ft_exit);
	else if (!ft_strncmp(str, "pwd", 3))
		return (&ft_pwd);
	else if (!ft_strncmp(str, "cd", 2))
		return (&ft_cd);
	else if (!ft_strncmp(str, "echo", 4))
		return (&ft_echo);
	else if (!ft_strncmp(str, "env", 3))
		return (&ft_env);
	else if (!ft_strncmp(str, "export", 6))
		return (&ft_export);
	else
		return (NULL);
}

static void	split_in_cmd(char **str_piped, t_shell *shell, t_parsing *parsing)
{
	int			i;
	t_cmd		*tmp;

	i = 0;
	i = 0;
	if (shell->error)
		return ;
	shell->cmd = ft_fill_cmd(str_piped[i++], shell, parsing);
	tmp = shell->cmd;
	if (tmp->infile == -2)
		tmp->infile = 0;
	while (str_piped[i])
	{
		tmp->next = ft_fill_cmd(str_piped[i], shell, parsing);
		if (!str_piped[i + 1] && tmp->outfile == -2)
			tmp->outfile = 1;
		tmp = tmp->next;
		i++;
	}
	ft_free_tab(str_piped);
}

void	ft_parsing(t_shell *shell, char *str)
{
	t_parsing	parsing;

	if (!str || !str[0])
	{	
		free(str);
		return ;
	}
	add_history(str);
	if (!strcmp(str, "exit"))
	{
		rl_clear_history();
		free(str);
		ft_clear_shell(shell);
		exit(0);
	}
	parsing.quote = NULL;
	ft_cut_quote_space(str, &parsing, shell);
	split_in_cmd(ft_split(str, '|'), shell, &parsing);
	free(str);
}
