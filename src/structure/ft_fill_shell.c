/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:57:06 by bastien           #+#    #+#             */
/*   Updated: 2023/08/31 14:08:32 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_create_export_i(t_shell *shell)
{
	char	**env;
	char	*tmp;
	t_env	*new;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return ;
	tmp = getcwd(NULL, 0);
	env[0] = ft_strjoin("PWD=", tmp);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = NULL;
	shell->export = ft_fill_env(env, -1);
	if (!tmp || !env[0] || !env[1])
		ft_clear_env(&shell->export);
	ft_free_tab(env);
	free(tmp);
	if (!shell->export)
		return ;
	new = ft_create_var_export("OLDPWD");
	if (new)
		lst_add_end(&shell->export, new);
	else
		ft_clear_env(&shell->export);
}

static void	ft_create_env_i(t_shell *shell)
{
	char	**env;
	char	*tmp;

	env = malloc(sizeof(char *) * 4);
	if (!env)
		return ;
	tmp = getcwd(NULL, 0);
	env[0] = ft_strjoin("PWD=", tmp);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	if (!tmp || !env[0] || !env[1] || !env[2])
	{
		ft_free_tab(env);
		if (tmp)
			free(tmp);
		return ;
	}
	shell->env = ft_fill_env(env, -1);
	ft_free_tab(env);
	free(tmp);
	ft_create_export_i(shell);
}

static void	upgrade_shlvl(t_env *env)
{
	t_env	*tmp;
	int		nb;

	tmp = env;
	while (tmp && ft_strncmp(tmp->name, "SHLVL", 6))
		tmp = tmp->next;
	if (tmp)
	{
		nb = ft_atoi(tmp->value);
		if (nb < 255)
		{
			free(tmp->value);
			tmp->value = ft_itoa(nb + 1);
			free(tmp->str);
			tmp->str = join_three(tmp->name, "=", tmp->value);
			if (!tmp->value || !tmp->str)
				ft_clear_env(&env);
		}
	}
}

t_shell	*ft_fill_shell(char **env)
{
	t_shell	*shell;

	shell = ft_init_shell();
	if (!shell)
		return (NULL);
	if (env[0])
	{
		shell->env = ft_fill_env(env, -1);
		shell->export = ft_fill_env(env, -1);
		upgrade_shlvl(shell->env);
		upgrade_shlvl(shell->export);
	}
	else
		ft_create_env_i(shell);
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
