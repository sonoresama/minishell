/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:10:26 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/23 10:24:47 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_args(char **args, int *option)
{
	int	i;

	i = 1;
	if (!ft_strncmp(args[i], "-n", 2))
		*option = 1;
}

static char	*get_env_value(char *var, t_shell *shell)
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

static void	print_env_value(char *var, t_shell *shell)
{
	char	*value;

	value = get_env_value(var, shell);
	if (!value)
		return ;
	else
		printf("%s", value);
}

static void	print_args(t_shell *shell)
{
	int	i;
	char	**args;

	i = 1;
	args = shell->cmd->exec.args;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] != ' ')
			print_env_value(args[i] + 1, shell);
		else
			printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
}

int	ft_echo(t_shell *shell)
{
	int	option;
	t_cmd	*cmd;

	cmd = shell->cmd;
	option = 0;
	if (!cmd->exec.args || !cmd->exec.args[1])
		return (0);
	check_args(cmd->exec.args, &option);
	print_args(shell);
	if (!option)
		printf("\n");
	return (0);
}
