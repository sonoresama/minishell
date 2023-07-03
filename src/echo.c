/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/07/03 12:21:16 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_args(char **args, int *option)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (args[j] && args[j][i])
	{
		if (args[j][i] != '-')
			return (j);
		i++;
		while (args[j][i])
		{
			if (args[j][i] != 'n')
				return (j);
			i++;
		}
		*option = 1;
		i = 0;
		j++;
	}
	return (j);
}

static void	print_args(t_shell *shell, int i)
{
	char	**args;

	args = shell->cmd->exec.args;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
}

void	ft_echo(t_shell *shell)
{
	int	option;
	int	start;
	t_cmd	*cmd;

	cmd = shell->cmd;
	option = 0;
	if (!cmd->exec.args || !cmd->exec.args[1])
	{
		printf("\n");
		return ;
	}
	start = check_args(cmd->exec.args, &option);
	print_args(shell, start);
	if (!option)
		printf("\n");
}
