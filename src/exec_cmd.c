/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:03:57 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_cmd *cmd)
{
	int	error;

	error = 0;
	if (cmd->built_in)
		error = cmd->built_in(cmd);
	else if(execve(cmd->exec.cmd_path, cmd->exec.args, cmd->env) == -1)
	{
		free_cmd(cmd);
		perror("ERREUR ");
	}
	exit(error);
}

void	ft_cmd(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == (pid_t)-1)
		perror("ERREUR ");
	else if (pid != 0)
		wait(&cmd->last_error);
	else
		exec_cmd(cmd);
}
