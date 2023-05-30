/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/05/30 15:02:23 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_args(char **args, int *option)
{
	int	i;

	i = 0;
	if (args[1][i] == '-')
	{
		i++;
		while (args[1][i])
		{
			if (args[1][i] != 'n')
				return ;
			i++;
		}
		*option = 1;
	}
}

char	*get_env_value(char *var, t_shell *shell)
{
	t_env	*lst;
	
	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(var, lst->name, ft_strlen(var)))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	print_env_value(char *var, t_shell *shell)
{
	char	*value;

	value = get_env_value(var, shell);
	if (!value)
		return ;
	else
		printf("%s", value);
}

void	print_args(t_shell *shell, int option)
{
	int	i;
	char	**args;

	i = 1;
	args = shell->cmd->exec.args;
	if (option)
		i++;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] != ' ')
		{
			//printf("TEST\n");
			print_env_value(args[i] + 1, shell);
		}
		else
			printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
}

int	ft_echo(t_shell *shell)
{
	int	i;
	int	option;
	t_cmd	*cmd;

	cmd = shell->cmd;
	option = 0;
	i = 1;
	if (!cmd->exec.args || !cmd->exec.args[1])
		return (0);
	check_args(cmd->exec.args, &option);
	print_args(shell, option);
	if (!option)
		printf("\n");
	return (0);
}
