/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <blerouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:48:39 by blerouss          #+#    #+#             */
/*   Updated: 2023/07/22 13:05:01 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstlen(t_env *env)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

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
