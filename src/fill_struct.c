/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:38:28 by blerouss          #+#    #+#             */
/*   Updated: 2023/06/01 17:56:45 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*ft_fill_shell(char **env)
{
	t_shell	*shell;

	shell = ft_init_shell();
	if (!shell)
		return (NULL);
	shell->maxi_env = env;
	shell->env = ft_fill_env(env, 0);
	if (!shell->env)
	{
		ft_clear_shell(shell);
		return (NULL);
	}
	return (shell);
}

void	ft_fill_exec(char *str, t_shell *shell, t_exec *exec, t_parsing *pars)
{
	char	*tmp;
	int		i;

	i = 0;
	(*exec).cmd_path = NULL;
	(*exec).args = ft_split(str, ' ');
	if (!(*exec).args)
		return ;
	ft_paste_quote_space((*exec).args, pars, shell);
	if ((*exec).args[0][0] == '<' || (*exec).args[0][0] == '>')
	{
		while ((*exec).args[i + 2])
		{
			(*exec).args[i] = (*exec).args[i + 2];
			i++;
		}
		(*exec).args[i] = NULL;
	}
	tmp = path_cmd((*exec).args[0], shell);
	if (!tmp)
		return ;
	free((*exec).args[0]);
	(*exec).args[0] = tmp;
	(*exec).cmd_path = tmp;
}

t_cmd	*ft_fill_cmd(char *str, t_shell *shell, t_parsing *parsing)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = ft_init_cmd();
	if (!cmd)
		return (NULL);
	cmd->heredoc = NULL;
	cmd->infile = -2;
	cmd->outfile = -2;
	i = ft_count_heredoc(str);
	if (i > 0)
	{
		cmd->heredoc = malloc(sizeof(char *) * (i + 1));
		if (!cmd->heredoc)
			return (NULL);
		cmd->heredoc[i] = NULL;
	}
	ft_fill_redir_heredoc(str, cmd);
	ft_fill_exec(str, shell, &cmd->exec, parsing);
	cmd->built_in = is_built_in(cmd->exec.args[0]);
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
		lst_env->str = env[i];
		while (env[i][j] != '=')
			j++;
		lst_env->name = ft_strndup(env[i], j);
		lst_env->value = &env[i][j + 1];
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
