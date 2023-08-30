/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:16:34 by eorer             #+#    #+#             */
/*   Updated: 2023/08/30 16:14:39 by blerouss         ###   ########.fr       */
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
	if (shell && shell->cmd && shell->cmd->heredoc && shell->cmd->heredoc[0])
	{
		if (unlink("heredoc") == -1)
			perror("UNLINK");
	}
	ft_clear_cmd(shell->cmd);
	shell->cmd = NULL;
	return ;
}

static void	print_fail_exit(t_shell *shell, struct stat *buf, t_cmd *cmd)
{
	char	*tmp;
	int		ex;

	if (!stat(cmd->exec.cmd_path, buf) && (S_ISDIR(buf->st_mode)
			|| S_ISREG(buf->st_mode)))
	{
		if (S_ISDIR(buf->st_mode))
			tmp = ft_strjoin(cmd->exec.args[0], ": Is a directory\n");
		else
			tmp = ft_strjoin(cmd->exec.args[0], ": Permission non accordée\n");
		ex = 126;
	}
	else
	{
		tmp = ft_strjoin(cmd->exec.args[0], ": commande introuvable\n");
		ex = 127;
	}
	if (!tmp)
		write(2, "Espace mémoire insuffisant.\n", 30);
	if (!tmp)
		ex = 1;
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	ft_clear_shell(shell);
	exit(ex);
}

static void	clear_and_quit(t_shell *shell)
{
	ft_clear_shell(shell);
	exit(0);
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
			g_sig_handle = 9;
			waitpid(pid, &shell->last_error, 0);
		}
		else if (cmd->exec.args[0] && execve(cmd->exec.cmd_path,
				cmd->exec.args, shell->maxi_env) == -1)
			print_fail_exit(shell, &buf, cmd);
		else
			clear_and_quit(shell);
	}
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
