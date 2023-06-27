/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:22:26 by eorer             #+#    #+#             */
/*   Updated: 2023/06/26 16:41:46 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close(int fd)
{
	if (fd > 1)
		close(fd);
}

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
		shell->pipein = get_input(shell->cmd, shell->pipein);
		shell->pipeout = get_output(shell->cmd, fd_pipe[1]);
		exec_cmd(shell);
		exit(shell->last_error);
	}
	else
	{
		close(fd_pipe[1]);
		shell->pipein = get_input(shell->cmd->next, fd_pipe[0]);
		shell->pipeout = get_output(shell->cmd->next, shell->pipeout);
//		waitpid(pid, &shell->last_error, 0);
	}
}
