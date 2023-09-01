/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:56:27 by bastien           #+#    #+#             */
/*   Updated: 2023/09/01 17:08:30 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_get_shlvl(t_shell *shell)
{
	t_env	*env;
	int	level;

	env = shell->env;
	while (env && ft_strncmp(env->name, "SHLVL", ft_strlen("SHLVL")))
		env = env->next;
	if (!env)
		return ;
	level = ft_atoi(env->value);
	free(env->value);
	free(env->str);
	free(env->name);
	env->name = ft_strdup("SHLVL");
	env->value = ft_itoa(level + 1);
	env->str = join_three(env->name, "=", env->value);
}

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
		while (env[i][j] != '=')
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
