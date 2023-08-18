/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:56:27 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 11:56:40 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_fill_env(char **env, int i)
{
	t_env	*lst_env;
	t_env	*lst_start;
	int		j;

	lst_env = ft_init_env();
	lst_start = lst_env;
	while (lst_start && env && env[i])
	{
		j = 0;
		lst_env->str = ft_strdup(env[i]);
		while (env[i][j] != '=')
			j++;
		lst_env->name = ft_strndup(env[i], j);
		lst_env->value = ft_strdup(&env[i][j + 1]);
		if (env[i + 1])
		{
			lst_env->next = ft_init_env();
			if (!lst_env->next)
				ft_clear_env(lst_start);
		}
		lst_env = lst_env->next;
		i++;
	}
	return (lst_start);
}
