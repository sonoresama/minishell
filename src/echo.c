/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:04:27 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	option;

	i = 1;
	if (!cmd->exec.args || !cmd->exec.args[1])
		return (0);
	if (!ft_strncmp(cmd->exec.args[0], "-n", 2))
	{
		option = 1;
		i++;
	}
	else
		option = 0;
	while(cmd->exec.args[i])
	{
		printf("%s", cmd->exec.args[i]);
		i++;
		if (cmd->exec.args[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}
