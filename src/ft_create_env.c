/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:30:10 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 15:39:18 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*lst_last(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lst_add_end(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst)
	{
		last = lst_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_env	*ft_init_lst(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	ft_bzero(env, sizeof(t_env));
	return (env);
}

t_env	*ft_create_var_env(char *str)
{
	t_env	*lst_env;
	int	i;

	i = 0;
	lst_env = ft_init_lst();
	if (!lst_env)
		return (NULL);
	lst_env->str = ft_strdup(str);
	while (str[i] != '=')
		i++;
	lst_env->name = ft_strndup(str, i);
	str = str + i + 1;
	lst_env->value = ft_strdup(str);
	lst_env->next = NULL;
	return (lst_env);
}

t_env	*ft_create_env(char **env)
{
	t_env	*lst_env;
	t_env	*begin;
	int	i;

	i = 0;
	lst_env = ft_init_lst();
	if (!lst_env)
		return (NULL);
	begin = lst_env;
	while (env && env[i])
	{
		lst_env = ft_create_var_env(env[i]);
		if (!lst_env)
		{
			perror("MALLOC ");
			return (NULL);
		}
		lst_add_end(&begin, lst_env);
		i++;
	}
	return (begin->next);
}
