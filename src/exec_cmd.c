/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 15:43:15 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_shell *shell)
{
	int	error;
	t_cmd	*cmd;

	error = 0;
	cmd = shell->cmd;
	if (cmd->built_in)
		error = cmd->built_in(shell);
	else if(execve(cmd->exec.cmd_path, cmd->exec.args, shell->maxi_env) == -1)
	{
		free_cmd(shell->cmd);
		perror("ERREUR ");
	}
	exit(error);
}

void	ft_cmd(t_shell *shell)
{
	pid_t	pid;

	if (shell->cmd->built_in)
	{
		shell->cmd->built_in(shell);
		return ;
	}
	pid = fork();
	if (pid == (pid_t)-1)
		perror("ERREUR ");
	else if (pid != 0)
		wait(&shell->last_error);
	else
		exec_cmd(shell);
}
