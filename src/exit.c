/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:31 by eorer             #+#    #+#             */
/*   Updated: 2023/06/08 19:23:44 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(t_shell *shell)
{
	int	sortie;
	t_cmd	*cmd;

	sortie = 0;
	cmd = shell->cmd;
	if (cmd->exec.args && cmd->exec.args[1])
		sortie = ft_atoi(cmd->exec.args[1]);
	ft_clear_shell(shell);
	rl_clear_history();
	exit(sortie);
	return (FT_EXIT);
}
