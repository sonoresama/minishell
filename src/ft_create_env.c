/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:30:10 by eorer             #+#    #+#             */
/*   Updated: 2023/08/21 16:30:08 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_create_var_env(char *str)
{
	t_env	*lst_env;
	int		i;

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
	int		i;

	i = 0;
	lst_env = ft_init_lst();
	if (!lst_env)
		return (NULL);
	begin = lst_env;
	while (env && env[i])
	{
		lst_env = ft_create_var_env(env[i]);
		if (!lst_env)
			return (NULL);
		lst_add_end(&begin, lst_env);
		i++;
	}
	return (begin->next);
}
