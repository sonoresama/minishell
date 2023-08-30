/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:36:25 by bastien           #+#    #+#             */
/*   Updated: 2023/08/30 16:52:39 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
