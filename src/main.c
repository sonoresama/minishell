/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/06/06 15:30:22 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int	set_cmd(char *str, t_shell *shell)
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
}*/

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = ft_fill_shell(env);
	if (!shell)
	{
		perror("INIT SHELL");
		return (1);
	}
	while (1)
	{
		if (ft_parsing(shell, readline("   \033[36m\033[1mMinishell \033[33m➜ \033[0m")) == -1)
		{
			perror("PARSING ");
			exit(1);
		}
		ft_cmd(shell);
		ft_clear_cmd(shell->cmd);
		shell->cmd = NULL;
		//ft_exit(shell);
	}
	return (0);
}
