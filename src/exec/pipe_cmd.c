/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:26 by eorer             #+#    #+#             */
/*   Updated: 2023/08/30 15:43:03 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_output(t_cmd *cmd, int pipe_out)
{
	if (cmd->outfile == -2)
		return (pipe_out);
	else
		return (cmd->outfile);
}

int	get_input(t_cmd *cmd, int pipe_in)
{
	int	fd;

	if (cmd->infile == -2)
		return (pipe_in);
	else if (cmd->infile == -3)
	{
		ft_heredoc(cmd->heredoc);
		fd = open("heredoc", O_RDWR);
		if (fd == -1)
			perror("OPEN");
		return (fd);
	}
	else if (cmd->heredoc)
		ft_heredoc(cmd->heredoc);
	return (cmd->infile);
}

void	pipe_child(t_shell *shell, int fd_in, int fd_out)
{
	ft_close(fd_in);
	shell->pipein = get_input(shell->cmd, shell->pipein);
	shell->pipeout = get_output(shell->cmd, fd_out);
	exec_cmd(shell);
	fd_in = shell->last_error;
	ft_clear_shell(shell);
	exit(fd_in);
}

void	pipe_parent(t_shell *shell, int fd_in, int fd_out)
{
	close(fd_out);
	ft_close(shell->pipein);
	ft_close(shell->pipeout);
	shell->pipein = get_input(shell->cmd->next, fd_in);
	shell->pipeout = get_output(shell->cmd->next, shell->pipeout);
}

void	pipe_cmd(t_shell *shell)
{
	pid_t	pid;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		perror("PIPE");
		exit(1);
	}
	pid = fork();
	if (pid == (pid_t)-1)
		perror("FORK");
	else if (pid == 0)
		pipe_child(shell, fd_pipe[0], fd_pipe[1]);
	g_sig_handle = pid;
	if (shell->cmd->next)
		pipe_parent(shell, fd_pipe[0], fd_pipe[1]);
	else
	{
		close(fd_pipe[1]);
		ft_close(shell->pipein);
		ft_close(shell->pipeout);
	}
}
