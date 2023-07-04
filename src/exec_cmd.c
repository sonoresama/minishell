/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/07/04 16:30:49 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	reset_shell(t_shell *shell)
{
	dup2(shell->fd_stdin, 0);
	dup2(shell->fd_stdout, 1);
	ft_close(shell->pipein);
	shell->pipein = 0;
	shell->pipeout = 1;
}

void	ft_print_args(t_shell *shell)
{
	t_cmd	*cmd;

//	return ;
	cmd = shell->cmd;
	printf("CMD : %s\n", cmd->exec.cmd_path); 
	printf("ARGS : %s\n", cmd->exec.args[1]); 
	printf("Pipe in : %i\n", shell->pipein); 
	printf("Pipe out : %i\n", shell->pipeout); 
	printf("Std in : %i\n", shell->fd_stdin); 
	printf("Std out : %i\n", shell->fd_stdout); 
	printf("Infile : %i\n", shell->cmd->infile); 
	printf("Outfile : %i\n\n", shell->cmd->outfile); 
}

void	exec_bin(t_shell *shell)
{
	pid_t	pid;
	t_cmd	*cmd;
	struct stat    buf;

	cmd = shell->cmd;
	pid = fork(); 
	if (pid == (pid_t)-1) 
		perror("FORK");
 	else if (pid != 0)
   	waitpid(pid, &shell->last_error, 0); 
	else if (execve(cmd->exec.cmd_path, cmd->exec.args, shell->maxi_env) == -1)
	{
		if (!stat(cmd->exec.cmd_path, &buf) && S_ISDIR(buf.st_mode))
	  {
			printf("%s: Is a directory\n", cmd->exec.args[0]);
			ft_clear_shell(shell);
			exit(126);
		}
		else
		{
			printf("%s: commande introuvable\n", cmd->exec.args[0]);
			ft_clear_shell(shell);
			exit(127);
		}
	}
	else 
		shell->last_error = 0;
}

void	exec_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	cmd = shell->cmd; 

	ft_print_args(shell);
	if (shell->pipein == -1 || shell->pipeout == -1)
		return ;
	dup2(shell->pipein, 0); 
	dup2(shell->pipeout, 1); 
	if (cmd->built_in) 
	{
		cmd->built_in(shell); 
		shell->last_error = 0;
	}
	else 
		exec_bin(shell);
	return ;
}

void	ft_wait(int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		wait(NULL);
		i++;
	}
	return ;
}

void	ft_cmd(t_shell *shell)
{
	int	i;
	t_cmd	*start;

	start = shell->cmd;
	i = 0;
	while (shell->cmd->next)
	{
		pipe_cmd(shell);
		shell->cmd = shell->cmd->next;
		i++;
	}
	shell->pipein = get_input(shell->cmd, shell->pipein);
	shell->pipeout = get_output(shell->cmd, shell->pipeout);
	exec_cmd(shell);
	shell->cmd = start;
	reset_shell(shell);
	ft_wait(i);
	if (shell->cmd->heredoc)
	{
		if (unlink("heredoc") == -1)
			perror("UNLINK");
	}
}
