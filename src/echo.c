/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 15:46:03 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_mini *mini)
{
	int	i;
	int	option;

	i = 0;
	if (!mini->args || !mini->args[0])
		return ;
	if (!ft_strncmp(mini->args[0], "-n", 2))
	{
		option = 1;
		i++;
	}
	else
		option = 0;
	while(mini->args[i])
	{
		printf("%s", mini->args[i]);
		i++;
		if (mini->args[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
}
