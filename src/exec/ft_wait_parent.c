/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:18:37 by blerouss          #+#    #+#             */
/*   Updated: 2023/09/11 17:20:28 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_wait_parent(pid_t pid, t_shell *shell, t_cmd *cmd)
{
	g_sig_handle = pid;
	if (!strncmp(cmd->exec.cmd_path, "./minishell", 12))
		unset_sig_handler();
	waitpid(pid, &shell->last_error, 0);
	if (!strncmp(cmd->exec.cmd_path, "./minishell", 12))
		init_sig_handler();
}
