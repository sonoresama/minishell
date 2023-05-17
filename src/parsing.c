/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/05/17 16:30:47 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_cmd(t_parsing *parsing, t_cmd *cmd)
{
	int	i;

	i = 0;
	parsing->cmd_line = ft_split(parsing->str_piped[parsing->utils], ' ');
	if (parsing->cmd_line[0][0] != '<' && parsing->cmd_line[0][0] != '>')
		cmd->args = parsing->cmd_line;
	else
	{
		while (parsing->cmd_line[i + 2])
		{
			parsing->cmd_line[i] = parsing->cmd_line[i + 2];
			i++;
		}
		parsing->cmd_line[i] = NULL;
		cmd->args = parsing->cmd_line;
	}
}

/*My_func	is_built_in(char *str)
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
	else
		return (NULL);
}*/

void	ft_parsing(t_cmd *cmd, t_cmd *start)
{
	t_parsing	parsing;

	parsing.str = readline("  \033[36m\033[1mMinishell \033[33m➜ \033[0m");
	add_history(parsing.str);
	//cmd->built_in = is_built_in(parsing.str);
	if (!strcmp(parsing.str, "exit"))
	{
		rl_clear_history();
		free(parsing.str);
		free(cmd);
		exit(0);
	}
	//gestion heredoc
	//gestion quote
	parsing.str_piped = ft_split(parsing.str, '|');
	free(parsing.str);
	parsing.utils = 0;
	while (parsing.str_piped[parsing.utils])
	{
		parse_cmd(&parsing, cmd);
		//parsing.str = path_cmd(cmd->args[0], cmd->env);
		free(cmd->args[0]);
		cmd->args[0] = parsing.str;
		parsing.utils++;
		if (parsing.str_piped[parsing.utils])
			ft_init_cmd_2(&cmd->next, NULL, cmd->env);
		cmd = cmd->next;
	}
	ft_free_tab(parsing.str_piped);
	ft_clear_cmd(start);
}
