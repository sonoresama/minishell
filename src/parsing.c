/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/05/22 15:09:30 by blerouss         ###   ########.fr       */
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
//	else if (!ft_strncmp(str, "unset", 5))
//		return (&ft_unset);
	else
		return (NULL);
}

t_shell	*ft_parsing(char **env, char *str)
{
	t_parsing	parsing;
	t_cmd		*tmp;
	t_shell		*shell;

	if (!str || !str[0])
		return (NULL);
	add_history(str);
	shell = ft_fill_shell(env);
	if (!strcmp(str, "exit"))
	{
		rl_clear_history();
		free(str);
		ft_clear_shell(shell);
		exit(0);
	}
	//gestion heredoc
	//gestion quote
	parsing.str_piped = ft_split(str, '|');
	free(str);
	parsing.utils = 0;
	shell->cmd = ft_fill_cmd(parsing.str_piped[parsing.utils++], shell);
	tmp = shell->cmd;
	while (parsing.str_piped[parsing.utils])
	{
		if (parsing.str_piped[parsing.utils])
			tmp->next = ft_fill_cmd(parsing.str_piped[parsing.utils], shell);
		tmp = tmp->next;
		parsing.utils++;
	}
	ft_free_tab(parsing.str_piped);
	return (shell);
}
