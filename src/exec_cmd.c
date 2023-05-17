/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/05/17 16:18:10 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_shell *shell)
{
	int	error;

	error = 0;
	if (shell->cmd->built_in)
		error = shell->cmd->built_in(shell->cmd);
	else if(execve(shell->cmd->exec.cmd_path, shell->cmd->exec.args, shell->cmd->env) == -1)
	{
		free_cmd(shell->cmd);
		perror("ERREUR ");
	}
	exit(error);
}

void	ft_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == (pid_t)-1)
		perror("ERREUR ");
	else if (pid != 0)
		wait(&shell->last_error);
	else
		exec_cmd(shell);
}
