/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:38:28 by blerouss          #+#    #+#             */
/*   Updated: 2023/08/14 16:45:35 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*ft_fill_shell(char **env)
{
	t_shell	*shell;

	shell = ft_init_shell();
	if (!shell)
		return (NULL);
	shell->env = ft_fill_env(env, 0);
	shell->export = ft_fill_env(env, 0);
	if (!shell->env || !shell->export)
	{
		ft_clear_shell(shell);
		return (NULL);
	}
	update_env(shell);
	shell->pipein = 0;
	shell->pipeout = 1;
	shell->fd_stdin = dup(0);
	shell->fd_stdout = dup(1);
	return (shell);
}

int	ft_fill_exec(char *str, t_shell *shell, t_exec *exec, t_parsing *pars)
{
	(*exec).cmd_path = NULL;
	(*exec).args = ft_split_2_separator(str, ' ', '	');
	if (!(*exec).args)
		return (1);
	ft_paste_quote_space((*exec).args, pars, shell);
	if (is_built_in(exec->args[0]))
		exec->cmd_path = ft_strdup(exec->args[0]);
	else
		exec->cmd_path = path_cmd((*exec).args[0], shell, -1);
	return (0);
}

t_cmd	*ft_fill_cmd(char *str, t_shell *shell, t_parsing *parsing)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = ft_init_cmd();
	if (!cmd)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	cmd->heredoc = NULL;
	cmd->infile = -2;
	cmd->outfile = -2;
	i = ft_count_heredoc(str);
	if (i > 0)
	{
		cmd->heredoc = malloc(sizeof(char *) * (i + 1));
		if (!cmd->heredoc)
		{
			shell->error = MALLOC_ERROR;
			ft_clear_cmd(cmd);
			return (NULL);
		}
		while (i > -1)	
			cmd->heredoc[i--] = NULL;
	}
	if (ft_fill_redir_heredoc(str, cmd, shell, parsing))
	{
		ft_clear_cmd(cmd);
		return (NULL);
	}
	if (cmd->infile == -1 || cmd->outfile == -1)
		shell->last_error = 1;
	if (ft_fill_exec(str, shell, &cmd->exec, parsing))
	{
		shell->error = MALLOC_ERROR;
		ft_clear_cmd(cmd);
		return (NULL);
	}
	cmd->built_in = is_built_in(cmd->exec.cmd_path);
	g_sig_handle = 10;
	return (cmd);
}

t_env	*ft_fill_env(char **env, int i)
{
	t_env	*lst_env;
	t_env	*lst_start;
	int		j;

	lst_env = ft_init_env();
	lst_start = lst_env;
	while (lst_start && env && env[i])
	{
		j = 0;
		lst_env->str = ft_strdup(env[i]);
		while (env[i][j] != '=')
			j++;
		lst_env->name = ft_strndup(env[i], j);
		lst_env->value = ft_strdup(&env[i][j + 1]);
		if (env[i + 1])
		{
			lst_env->next = ft_init_env();
			if (!lst_env->next)
				ft_clear_env(lst_start);
		}
		lst_env = lst_env->next;
		i++;
	}
	return (lst_start);
}
