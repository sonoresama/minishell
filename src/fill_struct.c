/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:38:28 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/19 17:36:22 by blerouss         ###   ########.fr       */
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
	shell->env = ft_fill_env(env);
	if (!shell->env)
		return (NULL);
	return (shell);
}

t_exec	ft_fill_exec(char *str, t_shell *shell)
{
	t_exec	exec;
	char	*tmp;
	int	i;

	i = 0;
	exec.args = ft_split(str, ' ');
	if (exec.args[0][0] == '<' || exec.args[0][0] == '>')
	{
		while (exec.args[i + 2])
		{
			exec.args[i] = exec.args[i + 2];
			i++;
		}
		exec.args[i] = NULL;
	}
	tmp = path_cmd(exec.args[0], shell);
	if (!tmp)
	{	
		ft_free_tab(exec.args);
		exec.args = NULL;
		exec.cmd_path = NULL;
		return (exec);
	}
	free(exec.args[0]);
	exec.args[0] = tmp;
	exec.cmd_path = tmp;
	return (exec);
}

t_cmd	*ft_fill_cmd(char *str, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = ft_init_cmd();
	if(!cmd)
		return (NULL);
	cmd->exec = ft_fill_exec(str, shell);
	if (!cmd->exec.args && !cmd->exec.cmd_path)
		return (NULL);
	return (cmd);
}

t_env	*ft_fill_env(char **env)
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
		lst_env->name = ft_strndup(env[i], j);
		lst_env->value = &env[i][j + 1];
		if (env[i + 1])
			lst_env->next = ft_init_env();
		lst_env = lst_env->next;
		i++;
	}
	return (lst_start);
}
