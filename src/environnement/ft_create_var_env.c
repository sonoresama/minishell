/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_var_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:02:47 by bastien           #+#    #+#             */
/*   Updated: 2023/08/28 15:05:15 by bastien          ###   ########.fr       */
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
	if (!lst_env->name || !lst_env->value || !lst_env->str)
	{
		ft_clear_env(&lst_env);
		return (NULL);
	}
	return (lst_env);
}
