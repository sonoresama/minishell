/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:08 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/24 17:17:57 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *var, t_shell *shell)
{
	t_env	*lst;
	
	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(var, lst->name, ft_strlen(var)))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

