/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:30:12 by eorer             #+#    #+#             */
/*   Updated: 2023/07/03 16:17:53 by emileorer        ###   ########.fr       */
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

int	check_doublon_export(t_env *new, t_shell *shell)
{
	t_env	*lst;

	lst = shell->export;
	while (lst)
	{
		if (!ft_strncmp(new->name, lst->name, ft_strlen(new->str)))
		{
			if (ft_strncmp(new->value, lst->value, ft_strlen(new->value) + 1))
			{
				if (lst->value)
					free(lst->value);
				lst->value = ft_strdup(new->value);
			}
			else
				return (1);
			free(lst->str);
			lst->str = ft_strdup(new->str);
			return (1);
		}
		lst = lst->next;
	}
	return(0);
}

int	check_doublon_env(t_env *new, t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	if (!new->value)
		return (1);
	while (lst)
	{
		if (!ft_strncmp(new->name, lst->name, ft_strlen(new->str) + 1))
		{
			if (ft_strncmp(new->value, lst->value, ft_strlen(new->value) + 1))
			{
				free(lst->value);
				lst->value = ft_strdup(new->value);
				free(lst->str);
				lst->str = ft_strdup(new->str);
			}
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_env	*create_new(char *str, t_shell *shell)
{
	t_env	*new;

	if (!search_equal(str))
		new = ft_create_var_export(str);
	else
		new = ft_create_var_env(str);
	if (!new)
	{
		shell->last_error = 1;
		write(2, "ERROR : malloc exploded\n", 24);
		return (NULL);
	}
	return (new);
}

void	add_export(char *str, t_shell *shell)
{
	t_env	*new;

	new = create_new(str, shell);
	if (!new)
		return ;
	if (check_doublon_export(new, shell))
	{
		free_env(new);
		return ;
	}
	lst_add_end(&shell->export, new);
	return ;
}

void	add_env(char *str, t_shell *shell)
{
	t_env	*new;

	new = create_new(str, shell);
	if (!new)
		return ;
	if (check_doublon_env(new, shell))
	{
		free_env(new);
		return ;
	}
	lst_add_end(&shell->env, new);
	return ;
}

void	ft_export(t_shell *shell)
{
	char	**args;
	int	i;

	args = shell->cmd->exec.args;
	i = 1;
	if (!args[i])
	{
		ft_env_export(shell);
		return ;
	}
	while (args[i])
	{
		if (!check_export(args[i], shell))
		{
			add_export(args[i], shell);
			add_env(args[i], shell);
		/*	new = create_new(args[i], shell);
			if (!new)
			{
				free(new);
				continue ;
			}
			printf("value : %s\n", new->value);
			if (new->value)
			{
				printf("add env \n");
				lst_add_end(&shell->env, new);
			}
			lst_add_end(&shell->export, new);*/
		}
		i++;
	}
	if (update_env(shell))
		perror("MALLOC");
}
