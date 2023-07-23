/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:31 by eorer             #+#    #+#             */
/*   Updated: 2023/07/23 12:15:17 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_shell *shell)
{
	int		sortie;
	t_cmd	*cmd;

	sortie = shell->last_error;
	cmd = shell->cmd;
	if (cmd && cmd->exec.args && cmd->exec.args[1])
		sortie = ft_atoi(cmd->exec.args[1]);
	ft_clear_shell(shell);
	rl_clear_history();
	printf("exit\n");
	exit(sortie);
}
