/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:31 by eorer             #+#    #+#             */
/*   Updated: 2023/06/26 14:17:21 by emileorer        ###   ########.fr       */
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
//	rl_clear_history();
	printf("exit\n");
	exit(sortie);
	return (FT_EXIT);
}
