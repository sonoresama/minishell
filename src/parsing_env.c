/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:38:28 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/17 17:08:31 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*ft_init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	ft_bzero(env, sizeof(t_env));
	return (env);
}

t_env	*ft_parse_env(char **env)
{
	t_env	*lst_env;
	t_env	*lst_start;
	int	i;
	int	j;

	i = 0;
	lst_env = ft_init_env();
	lst_start = lst_env;
	while (env && env[i])
	{
		j = 0;
		lst_env->str = env[i];
		while (env[i][j] != '=')
			j++;
		lst_env->name = ft_strndup(env[i], j - 1);
		lst_env->value = &env[i][j + 1];
		if (env[i + 1])
			lst_env->next = ft_init_env();
		lst_env = lst_env->next;
		i++;
	}
	return (lst_start);
}
