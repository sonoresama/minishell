/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/05/12 17:46:42 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(t_mini *mini)
{
	int	i;
	int	option;

	i = 1;
	if (!mini->exec.args || !mini->exec.args[1])
		return (0);
	if (!ft_strncmp(mini->exec.args[0], "-n", 2))
	{
		option = 1;
		i++;
	}
	else
		option = 0;
	while(mini->exec.args[i])
	{
		printf("%s", mini->exec.args[i]);
		i++;
		if (mini->exec.args[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}
