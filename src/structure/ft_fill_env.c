/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:56:27 by bastien           #+#    #+#             */
/*   Updated: 2023/08/31 12:29:18 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_fill_env(char **env, int i)
{
	t_env	*lst;
	t_env	*lst_start;
	int		j;

	lst = ft_init_env();
	lst_start = lst;
	while (lst_start && env && env[++i])
	{
		j = 0;
		lst->str = ft_strdup(env[i]);
		while (env[i][j] && env[i][j] != '=')
			j++;
		lst->name = ft_strndup(env[i], j);
		lst->value = ft_strdup(&env[i][j + 1]);
		if (env[i + 1] || !lst->str || !lst->name || !lst->value)
		{
			lst->next = ft_init_env();
			if (!lst->next || !lst->str || !lst->name || !lst->value)
				ft_clear_env(&lst_start);
			if (!lst_start)
				return (NULL);
		}
		lst = lst->next;
	}
	return (lst_start);
}
