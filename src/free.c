/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:29:34 by eorer             #+#    #+#             */
/*   Updated: 2023/07/03 14:03:30 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau && tableau[i])
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_all(t_shell *shell)
{
	free(shell->cmd->exec.cmd_path);
	free_tab(shell->cmd->exec.args);
	free(shell->cmd);
//	free(shell->maxi_env);
//	free_tab(shell->maxi_env);
//	free(shell->str);
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	if (env->str)
		free(env->str);
	free(env);
}
