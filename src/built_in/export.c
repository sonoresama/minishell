/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:30:12 by eorer             #+#    #+#             */
/*   Updated: 2023/08/21 16:39:47 by bastien          ###   ########.fr       */
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

static void	append_new_var(t_env *new, t_env *lst)
{
	char	*tmp;

	new->name[ft_strlen(new->name) - 1] = '\0';
	tmp = ft_strjoin(lst->value, new->value);
	free(lst->value);
	lst->value = tmp;
	tmp = ft_strjoin(lst->str, new->value);
	free(lst->str);
	lst->str = tmp;
}

static int	check_doublon_env(t_env *new, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(new->name, tmp->name, ft_strlen(new->name) + 1)
			|| (!ft_strncmp(new->name, tmp->name, ft_strlen(new->name) - 1)
				&& new->name[ft_strlen(new->name) - 1] == '+'))
		{
			if (new->name[ft_strlen(new->name) - 1] == '+')
				append_new_var(new, tmp);
			else
			{
				free(tmp->value);
				tmp->value = ft_strdup(new->value);
				free(tmp->str);
				tmp->str = ft_strdup(new->str);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	add_env(char *str, t_shell *shell)
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
		return ;
	}
	if (!check_doublon_env(new, shell->env) && new->value)
	{
		lst_add_end(&shell->env, ft_create_var_env(str));
		if (!check_doublon_env(new, shell->export))
			lst_add_end(&shell->export, new);
		else
			free_env(new);
	}
	else if (!check_doublon_env(new, shell->export))
		lst_add_end(&shell->export, new);
	else
		free_env(new);
	return ;
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
			add_env(args[i], shell);
		i++;
	}
	if (update_env(shell))
		shell->error = MALLOC_ERROR;
}
