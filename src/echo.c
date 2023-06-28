/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:29:18 by eorer             #+#    #+#             */
/*   Updated: 2023/06/28 16:53:40 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_args(char **args, int *option)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (args[j][i])
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
	char	*dup;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var && var[i])
	{
		if (var[i] == '$' && var[i + 1])
		{
			i++;
			if (var[i + j] == '$')
			{
				j++;
				dup = ft_strndup("$", 0);
			}
			else
			{
				while (var[i + j] && var[i + j] != '$')
					j++;
				dup = ft_strndup(var + i, j);
			}
			if (!dup)
				perror("MALLOC EXPLODED\n");
			value = get_env_value(dup, shell);
			if (value)
				printf("%s", value);
			free(dup);
		}
		else 
		{
			printf("$");
			return ;
		}
		i += j;
		j = 0;
	}
}

void	print_args(t_shell *shell, int option, int i)
{
	char	**args;

	(void)option;
	args = shell->cmd->exec.args;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			if (args[i][1] == '?')
				printf("%i", shell->last_error);
			else
				print_env_value(args[i], shell);
		}
		else
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
	print_args(shell, option, start);
	if (!option)
		printf("\n");
}
