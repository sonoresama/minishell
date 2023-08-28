/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:41:55 by bastien           #+#    #+#             */
/*   Updated: 2023/08/24 15:55:08 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nb_var(t_env *env)
{
	t_env	*lst;
	int		i;

	lst = env;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static int	ft_fill_mod_env(char **mod_env, t_env *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		mod_env[i] = ft_strdup(lst->str);
		if (!mod_env[i])
		{
			ft_free_tab(mod_env);
			return (1);
		}
		i++;
		lst = lst->next;
	}
	mod_env[i] = NULL;
	return (0);
}

int	update_env(t_shell *shell)
{
	t_env	*lst;
	char	**mod_env;

	lst = shell->env;
	mod_env = (char **)malloc(sizeof(char *) * (nb_var(shell->env) + 1));
	if (!mod_env || ft_fill_mod_env(mod_env, lst))
	{
		shell->error = MALLOC_ERROR;
		return (1);
	}
	if (shell->maxi_env)
		ft_free_tab(shell->maxi_env);
	shell->maxi_env = mod_env;
	return (0);
}
