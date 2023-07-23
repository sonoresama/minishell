/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emileorer <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:59 by emileorer         #+#    #+#             */
/*   Updated: 2023/07/23 14:17:10 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_create_var_export(char *str)
{
	t_env	*lst_env;
	int	i;

	i = 0;
	lst_env = ft_init_lst();
	if (!lst_env)
		return (NULL);
	lst_env->str = ft_strdup(str);
	if (!search_equal(str))
	{
		lst_env->name = ft_strdup(str);
		lst_env->value = NULL;
		lst_env->next = NULL;
		return (lst_env);
	}
	while (str[i] != '=')
		i++;
	lst_env->name = ft_strndup(str, i);
	str = str + i + 1;
	lst_env->value = ft_strdup(str);
	lst_env->next = NULL;
	return (lst_env);
}

t_env	*ft_create_export(char **env)
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
		lst_env = ft_create_var_export(env[i]);
		if (!lst_env)
		{
			perror("CREATE EXPORT ");
			return (NULL);
		}
		lst_add_end(&begin, lst_env);
		i++;
	}
	return (begin->next);
}
