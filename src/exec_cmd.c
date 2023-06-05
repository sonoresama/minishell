/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/06/05 12:10:34 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	exec_cmd(t_shell *shell)
{
	int	error;
	pid_t	pid;
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

void	init_infile(t_shell *shell, int nb)
{
	if (shell->cmd->infile == -1)
	{
		if (nb % 2 == 1)
		{
			close(shell->pipe_a[1]);
			shell->cmd->infile = shell->pipe_a[0];
		}
		else
		{
			close(shell->pipe_b[1]);
			shell->cmd->infile = shell->pipe_b[0];
		}
	}
}

void	init_outfile(t_shell *shell, int nb)
{
	if (shell->cmd->outfile == -1)
	{
		if (nb % 2 == 1)
		{
			close(shell->pipe_b[0]);
			shell->cmd->infile = shell->pipe_b[1];
		}
		else
		{
			close(shell->pipe_a[0]);
			shell->cmd->infile = shell->pipe_a[1];
		}
	}
}

void	exec_cmd(t_shell *shell)
{
	pid_t	pid;
	t_cmd	*cmd;
	My_func built_in;

	cmd = shell->cmd;
	built_in = is_built_in(cmd->exec.cmd_path);
	if (built_in)
		built_in(shell);
	else 
	{
		pid = fork();
		if (pid == (pid_t)-1)
			perror("ERREUR ");
		else if (pid != 0)
			wait(&shell->last_error);
		else if (execve(cmd->exec.cmd_path, cmd->exec.args, shell->maxi_env) == -1)
		{
			free_all(shell);
			perror("ERREUR ");
		}
	}
	return ;	
}

void	pipe_cmd(t_shell *shell, int nb)
{
	init_infile(shell, nb);
	init_outfile(shell, nb);
	dup2(shell->cmd->infile, 0);
	dup2(shell->cmd->outfile, 1);
	exec_cmd(shell);
}

void	ft_cmd(t_shell *shell)
{
	t_cmd	*start;
	int	i;

	i = 0;
	start = shell->cmd;
	while (shell->cmd)
	{
		pipe_cmd(shell, i);
		shell->cmd = shell->cmd->next;
		i++;
	}
	shell->cmd = start;
}*/
