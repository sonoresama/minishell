/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:36:08 by bastien           #+#    #+#             */
/*   Updated: 2023/08/28 16:36:37 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
