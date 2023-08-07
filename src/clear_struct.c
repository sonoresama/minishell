/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:46:46 by blerouss          #+#    #+#             */
/*   Updated: 2023/08/07 18:35:01 by bastien          ###   ########.fr       */
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
		free(env->str);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
	env = NULL;
}

void	ft_clear_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->maxi_env)
			ft_free_tab(shell->maxi_env);
		if (shell->export)
			ft_clear_env(shell->export);
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
		if (cmd->exec.cmd_path)
			free(cmd->exec.cmd_path);
		if (cmd->exec.args)
			ft_free_tab(cmd->exec.args);
		if (cmd->outfile > 2)
			close(cmd->outfile);
		if (cmd->infile > 2)
			close(cmd->infile);
		tmp = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = tmp;
	}
}

void	ft_clear_parsing(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing && parsing->heredoc && parsing->heredoc[i])
		free(parsing->heredoc[i++]);
	if (parsing && parsing->heredoc)
		free(parsing->heredoc);
	i = 0;
	while (parsing && parsing->redir && parsing->redir[i])
		free(parsing->redir[i++]);
	if (parsing && parsing->redir)
		free(parsing->redir);
	if (parsing && parsing->quote)
		ft_clear_quote(&parsing->quote);
	if (parsing && parsing->dquote)
		ft_clear_quote(&parsing->dquote);
	if (parsing)
		free(parsing);
}
