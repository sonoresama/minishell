/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 15:21:21 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	reset_shell(t_shell *shell, int num)
{
	int	i;

	i = shell->fd_stdout;
	dup2(shell->fd_stdin, 0);
	dup2(shell->fd_stdout, 1);
	while (i++ <= shell->pipein + 2)
		ft_close(i);
	i = -1;
	shell->pipein = 0;
	shell->pipeout = 1;
	while (++i < num)
		wait(NULL);
	if (shell && shell->cmd && shell->cmd->heredoc)
	{
		if (unlink("heredoc") == -1)
			perror("UNLINK");
	}
	return ;
}

static void	print_fail_exit(t_shell *shell, struct stat *buf, t_cmd *cmd)
{
	char	*tmp;

	if (!stat(cmd->exec.cmd_path, buf) && (S_ISDIR(buf->st_mode)
			|| S_ISREG(buf->st_mode)))
	{
		if (S_ISDIR(buf->st_mode))
			tmp = ft_strjoin(cmd->exec.args[0], ": Is a directory\n");
		else
			tmp = ft_strjoin(cmd->exec.args[0], ": Permission non accordée\n");
		write(2, tmp, ft_strlen(tmp));
		free(tmp);
		ft_clear_shell(shell);
		exit(126);
	}
	else
	{
		tmp = ft_strjoin(cmd->exec.args[0], ": commande introuvable\n");
		write(2, tmp, ft_strlen(cmd->exec.args[0]) + 23);
		free(tmp);
		ft_clear_shell(shell);
		exit(127);
	}
}

void	exec_cmd(t_shell *shell)
{
	t_cmd		*cmd;
	pid_t		pid;
	struct stat	buf;

	cmd = shell->cmd;
	dup2(shell->pipein, 0);
	dup2(shell->pipeout, 1);
	if (cmd->built_in)
		cmd->built_in(shell);
	else
	{
		pid = fork();
		if (pid == (pid_t) - 1)
			perror("FORK");
		else if (pid != 0)
		{
			g_sig_handle = pid;
			waitpid(pid, &shell->last_error, 0);
		}
		else if (cmd->exec.args[0] && execve(cmd->exec.cmd_path,
				cmd->exec.args, shell->maxi_env) == -1)
			print_fail_exit(shell, &buf, cmd);
	}
}

void	clear_pipe(t_shell *shell)
{
	if (shell->cmd->heredoc)
		ft_free_tab(shell->cmd->heredoc);
	if (shell->cmd->exec.cmd_path)
		free(shell->cmd->exec.cmd_path);
	if (shell->cmd->exec.args)
		ft_free_tab(shell->cmd->exec.args);
	ft_close(shell->cmd->outfile);
	ft_close(shell->cmd->infile);
}

void	ft_cmd(t_shell *shell)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	if (!shell->cmd->next)
	{
		shell->pipein = get_input(shell->cmd, shell->pipein);
		shell->pipeout = get_output(shell->cmd, shell->pipeout);
		exec_cmd(shell);
		reset_shell(shell, i);
		return ;
	}
	while (shell->cmd)
	{
		pipe_cmd(shell);
		tmp = shell->cmd->next;
		clear_pipe(shell);
		free(shell->cmd);
		shell->cmd = tmp;
		i++;
	}
	waitpid(g_sig_handle, &shell->last_error, 0);
	reset_shell(shell, i);
}
