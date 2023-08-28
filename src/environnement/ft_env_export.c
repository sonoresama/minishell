/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emileorer <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:55:36 by emileorer         #+#    #+#             */
/*   Updated: 2023/07/23 13:39:32 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a && b && a[i] && b[i])
	{
		if (a[i] > b[i])
			return (-1);
		else if (a[i] < b[i])
			return (1);
		i++;
	}
	if (b && a && !b[i] && a[i])
		return (-1);
	if (b && a && b[i] && !a[i])
		return (1);
	return (0);
}

void	ft_env_export(t_shell *shell, int i, char *old_tmp)
{
	t_env	*env;
	char	*tmp;

	while (i)
	{
		tmp = NULL;
		env = shell->export;
		while (env)
		{
			if ((!tmp && ((!old_tmp || ft_strcmp(env->name, old_tmp) == -1)))
				|| (ft_strcmp(tmp, env->name) < 0 && (!old_tmp
						|| ft_strcmp(env->name, old_tmp) < 0)))
				tmp = env->name;
			env = env->next;
		}
		old_tmp = tmp;
		env = shell->export;
		while (env && ft_strcmp(tmp, env->name))
			env = env->next;
		if (env->value)
			printf("export %s=\"%s\"\n", env->name, env->value);
		else
			printf("export %s\n", env->name);
		i--;
	}
}
