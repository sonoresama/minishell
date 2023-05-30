/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/30 14:32:22 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_cmd(char *str, t_shell *shell)
{
	char	**split;
	int	i;
	My_func	b_i;
	t_cmd	*cmd;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	split = ft_split(str, ' ');
	if (!split)
		return (1);
	b_i = is_built_in(split[0]);
	if (b_i)
		cmd->exec.cmd_path = ft_strdup(split[0]);
	else
		cmd->exec.cmd_path = path_cmd(split[0], shell, shell->cmd);
	cmd->exec.args = split;
	cmd->infile = 0;
	cmd->outfile = 1;
//	cmd->num = 0;
	cmd->next = NULL;
	shell->cmd = cmd;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	shell.env = ft_create_env(env);
	if (update_env(&shell))
	{
		perror("MALLOC");
		return (1);
	}
	if (!shell.env)
	{
		perror("MALLOC ");
		return (1);
	}
	while (1)
	{
		shell.str = readline("minishell$ ");
		if (!shell.str || !shell.str[0])
			continue;
		add_history(shell.str);
		if(set_cmd(shell.str, &shell))
		{
			perror("ERROR SET CMD ");
			exit(1);
		}
		ft_cmd(&shell);
		if (shell.last_error != FT_EXIT)
			free_all(&shell);
	}
	return (0);
}
