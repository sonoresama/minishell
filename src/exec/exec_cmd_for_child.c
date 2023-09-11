/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_for_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:05:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/09/11 17:16:23 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	ft_wait_child(pid_t pid, t_shell *shell, t_cmd *cmd)
{
	g_sig_handle = 9;
	if (!strncmp(cmd->exec.cmd_path, "./minishell", 12))
		unset_sig_handler();
	waitpid(pid, &shell->last_error, 0);
	if (!strncmp(cmd->exec.cmd_path, "./minishell", 12))
		init_sig_handler();
}

void	exec_cmd_for_child(t_shell *shell)
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
			ft_wait_child(pid, shell, cmd);
		else if (cmd->exec.args[0] && execve(cmd->exec.cmd_path,
				cmd->exec.args, shell->maxi_env) == -1)
			print_fail_exit(shell, &buf, cmd);
		else
			clear_and_quit(shell);
	}
}
