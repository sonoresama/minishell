/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:30:12 by eorer             #+#    #+#             */
/*   Updated: 2023/08/24 16:37:17 by bastien          ###   ########.fr       */
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

static void	stuck_new_var(t_env *new, t_env *lst)
{
	char	*tmp;

	if (new->name[ft_strlen(new->name) - 1] == '+')
	{
		new->name[ft_strlen(new->name) - 1] = '\0';
		tmp = ft_strjoin(lst->value, new->value);
		free(lst->value);
		lst->value = tmp;
		tmp = ft_strjoin(lst->str, new->value);
		free(lst->str);
		lst->str = tmp;
	}
	else
	{
		free(lst->value);
		lst->value = ft_strdup(new->value);
		free(lst->str);
		lst->str = ft_strdup(new->str);
	}
}

static int	check_doublon_env(t_env *new, t_env *lst, t_shell *shell)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(new->name, tmp->name, ft_strlen(new->name) + 1)
			|| (!ft_strncmp(new->name, tmp->name, ft_strlen(new->name) - 1)
				&& new->name[ft_strlen(new->name) - 1] == '+'))
		{
			stuck_new_var(new, lst);
			if (!tmp->value || !tmp->str)
				shell->error = MALLOC_ERROR;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	add_env(char *str, t_shell *shell)
{
	t_env	*new;

	if (!search_equal(str))
		new = ft_create_var_export(str);
	else
		new = ft_create_var_env(str);
	if (!new)
	{
		shell->last_error = 1;
		shell->error = MALLOC_ERROR;
		return (1);
	}
	if (!check_doublon_env(new, shell->env, shell) && new->value)
	{
		lst_add_end(&shell->env, new);
		if (!check_doublon_env(new, shell->export, shell))
			lst_add_end(&shell->export, ft_create_var_env(str));
	}
	else if (!check_doublon_env(new, shell->export, shell))
		lst_add_end(&shell->export, new);
	else
		free_env(new);
	if (shell->error == MALLOC_ERROR)
		return (1);
	return (0);
}

void	ft_export(t_shell *shell)
{
	char	**args;
	int		i;

	args = shell->cmd->exec.args;
	i = 1;
	if (!args[i])
	{
		ft_env_export(shell, ft_lstlen(shell->export), NULL);
		return ;
	}
	while (args[i])
	{
		if (!check_export(args[i], shell))
			if (add_env(args[i], shell))
			{
				update_env(shell);
				return ;
			}
		i++;
	}
	update_env(shell);
}
