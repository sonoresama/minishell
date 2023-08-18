/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:01:57 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 18:28:07 by bastien          ###   ########.fr       */
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

/* GERER LES FREE SI FT_STRDUP PLANTE */

int	update_env(t_shell *shell)
{
	t_env	*lst;
	char	**mod_env;
	int		i;

	lst = shell->env;
	i = 0;
	mod_env = (char **)malloc(sizeof(char *) * (nb_var(shell->env) + 1));
	if (!mod_env)
		return (1);
	while (lst)
	{
		mod_env[i] = ft_strdup(lst->str);
		i++;
		lst = lst->next;
	}
	mod_env[i] = NULL;
	if (shell->maxi_env)
		ft_free_tab(shell->maxi_env);
	shell->maxi_env = mod_env;
	return (0);
}
