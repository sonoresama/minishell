/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_var_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emileorer <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:24:59 by emileorer         #+#    #+#             */
/*   Updated: 2023/08/28 15:05:46 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*ft_create_var_export_without_value(char *str, t_env *lst_env)
{
	lst_env->name = ft_strdup(str);
	lst_env->value = NULL;
	lst_env->next = NULL;
	if (!lst_env->str || !lst_env->name)
	{
		ft_clear_env(&lst_env);
		return (NULL);
	}
	return (lst_env);
}

t_env	*ft_create_var_export(char *str)
{
	t_env	*lst_env;
	int		i;

	i = 0;
	lst_env = ft_init_lst();
	if (!lst_env)
		return (NULL);
	lst_env->str = ft_strdup(str);
	if (!search_equal(str))
		return (ft_create_var_export_without_value(str, lst_env));
	while (str[i] != '=')
		i++;
	lst_env->name = ft_strndup(str, i);
	lst_env->value = ft_strdup(&str[i + 1]);
	lst_env->next = NULL;
	if (!lst_env->str || !lst_env->name || !lst_env->value)
	{
		ft_clear_env(&lst_env);
		return (NULL);
	}
	return (lst_env);
}
