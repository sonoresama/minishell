/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:30:12 by eorer             #+#    #+#             */
/*   Updated: 2023/06/28 17:26:56 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_alpha(char a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return (1);
	return (0);
}

int	is_digit(char a)
{
	if (a >= 48 && a <= 57)
		return (1);
	return (0);
}

int	is_all_alpha_num(char *str)
{
	int	i;

	i = 0;
	if (!str || !is_alpha(str[i]))
		return (0);
	while (str[i] && (is_alpha(str[i]) || is_digit(str[i])))
		i++;
	if (!is_alpha(str[i]) && !is_digit(str[i]) && str[i])
		return (0);
	return (1);
}

int	check_export(char *str, t_shell *shell)
{
	if (!is_all_alpha_num(str))
	{
		shell->last_error = 1;
		write(2, "ERROR : no valid operator\n", 27);
		return (1);
	}
	if (str[0] == '=')
	{
		shell->last_error = 1;
		write(2, "ERROR : arg not found\n", 23);
		return (1);
	}
	if (!search_equal(str))
		return (1);
	return(0);
}

int	check_doublon(char *str, t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(str, lst->name, ft_strlen(str)))
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_env	*create_new(char *str, t_shell *shell)
{
	t_env	*new;

	new = ft_create_var_env(str);
	if (!new)
	{
		shell->last_error = 1;
		write(2, "ERROR : malloc exploded\n", 24);
		return (NULL);
	}
	if (check_doublon(new->name, shell))
		return (NULL);
	return (new);
}

void	ft_export(t_shell *shell)
{
	char	**args;
	t_env	*new;
	int	i;

	args = shell->cmd->exec.args;
	i = 1;
	if (!args[i])
	{
		ft_env(shell);
		return ;
	}
	while (args[i])
	{
		if (!check_export(args[i], shell))
		{
			new = create_new(args[i], shell);
			if (!new)
			{
				free(new);
				continue ;
			}
			else
				lst_add_end(&shell->env, new);
		}
		i++;
	}
	if (update_env(shell))
		perror("MALLOC");
}
