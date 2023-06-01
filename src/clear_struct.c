/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:46:46 by blerouss          #+#    #+#             */
/*   Updated: 2023/06/01 17:01:59 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_quote(t_quote **quote)
{
	t_quote	*tmp;

	while ((*quote))
	{
		free((*quote)->str);
		tmp = (*quote);
		(*quote) = (*quote)->next;
		free(tmp);
	}
	(*quote) = NULL;
}

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
		if (cmd->heredoc)
			ft_free_tab(cmd->heredoc);
		if (cmd->exec.args)
			ft_free_tab(cmd->exec.args);
		if (cmd->outfile > 2)
			close(cmd->outfile);
		if (cmd->infile > 2)
			close(cmd->infile);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
