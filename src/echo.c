/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/05/17 18:11:33 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	check_args(char **args, int *option, int *env)
{
	int	i;

	i = 1;
	if (!ft_strncmp(args[i], "-n", 2))
	{
		*option = 1;
		i++;
	}
	if (args[i][0] == '$')
}*/

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	option;
//	int	env;

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
