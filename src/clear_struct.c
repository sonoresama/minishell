/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:46:46 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/19 17:25:27 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->name);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	ft_clear_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->env)
			ft_clear_env(shell->env);
		if (shell->cmd)
			ft_clear_cmd(shell->cmd);	
		free(shell);
	}
}

void	ft_clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->exec.args)
		{
			ft_print_tab(cmd->exec.args);
			ft_free_tab(cmd->exec.args);
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
