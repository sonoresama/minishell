/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/06/06 15:44:17 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close(int fd)
{
	if (fd > 1)
		close(fd);
}

void	exec_cmd(t_shell *shell)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = shell->cmd;
	dup2(shell->pipein, 0);
	dup2(shell->pipeout, 1);
	if (cmd->built_in)
		cmd->built_in(shell);
	else 
	{
		pid = fork();
		if (pid == (pid_t)-1)
			perror("ERREUR ");
		else if (pid != 0)
			waitpid(pid, &shell->last_error, 0);
		else if (execve(cmd->exec.cmd_path, cmd->exec.args, shell->maxi_env) == -1)
		{
			free_all(shell);
			perror("ERREUR ");
		}
	}
	return ;	
}

void	pipe_cmd(t_shell *shell)
{
	pid_t	pid;
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		perror("PIPE");
		exit(1) ;
	}
	pid = fork();
	if (pid == (pid_t)-1)
		perror("FORK");
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		shell->pipeout = fd_pipe[1];
		exec_cmd(shell);
		exit(0);
	}
	else
	{
		close(fd_pipe[1]);
		shell->pipein = fd_pipe[0];
		waitpid(pid, &shell->last_error, 0);
	}
}

void	ft_cmd(t_shell *shell)
{
	t_cmd	*start;

	start = shell->cmd;
	while (shell->cmd->next)
	{
		pipe_cmd(shell);
		shell->cmd = shell->cmd->next;
	}
	exec_cmd(shell);
	dup2(shell->fd_stdin, 0);
	dup2(shell->fd_stdout, 1);
	ft_close(shell->pipein);
	shell->pipein = 0;
	shell->pipeout = 1;
	shell->cmd = start;
}
