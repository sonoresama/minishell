/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/06/08 17:09:27 by emileorer        ###   ########.fr       */
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
			exit(-1);
		}
	}
	return ;
}

int	write_heredoc(char *eof)
{
	int	fd;
	char	*str;

	fd = open("heredoc", O_CREAT | O_RDWR);
	if (fd == -1)
	{
		perror("OPEN");
		return (-1);
	}
	str = NULL;
	while (ft_strncmp(eof, str, ft_strlen(eof) + 1))
	{
		str = readline("heredoc>> ");
		write(fd, str, ft_strlen(str));
	}
	return (fd);
}

int	ft_heredoc(char **heredoc)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (heredoc[i])
	{
		if (fd)
		{
			if (unlink("heredoc") == -1)
			{
				perror("UNLINK");
				return (-1);
			}
		}
		fd = write_heredoc(heredoc[i]);
		if (fd == -1)
			return (-1);
		i++;
	}
	return (fd);
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
	if (cmd->infile == -2)
		return (pipe_in);
	//else if (cmd->infile == -3)
	//	return (ft_heredoc(cmd->heredoc));
	else if (cmd->heredoc)
		return (ft_heredoc(cmd->heredoc));
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
		waitpid(pid, &shell->last_error, 0);
	}
}

void	reset_shell(t_shell *shell)
{
	dup2(shell->fd_stdin, 0);
	dup2(shell->fd_stdout, 1);
	ft_close(shell->pipein);
	shell->pipein = 0;
	shell->pipeout = 1;
}

void	ft_cmd(t_shell *shell)
{
	while (shell->cmd->next)
	{
		pipe_cmd(shell);
		shell->cmd = shell->cmd->next;
	}
	shell->pipein = get_input(shell->cmd, shell->pipein);
	shell->pipeout = get_output(shell->cmd, shell->pipeout);
//	printf("input : %i\n", shell->pipein);
//	printf("output : %i\n", shell->pipeout);
//	printf("CMd : %s\n", shell->cmd->exec.cmd_path);
//	printf("Arg : %s\n", shell->cmd->exec.args[0]);
	exec_cmd(shell);
	if (shell->cmd->heredoc)
	{
		if (unlink("heredoc") == -1)
			perror("UNLINK");
	}
	reset_shell(shell);
}
