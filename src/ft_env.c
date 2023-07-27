/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/07/27 17:55:23 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (1);
	else
		return (0);
}

static char	**ft_copy_tab(char **tab, t_shell *shell)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static void	ft_change_var(t_shell *shell, int i)
{
	shell->cmd->built_in = NULL;
	free(shell->cmd->exec.cmd_path);
	if (is_built_in(shell->cmd->exec.args[i]))
	{
		shell->cmd->exec.cmd_path = ft_strdup(shell->cmd->exec.args[i]);
		shell->cmd->built_in = is_built_in(shell->cmd->exec.cmd_path);
	}
	else
		shell->cmd->exec.cmd_path = path_cmd(shell->cmd->exec.args[i],
				shell, -1);
}

static void	ft_exec_cmd(t_shell *shell, int i, char **tmp, struct stat buf)
{
	if (!shell->cmd->built_in && (access(shell->cmd->exec.cmd_path, F_OK)
			|| !ft_strchr(shell->cmd->exec.cmd_path, '/')))
	{
		printf("env: «%s»: Aucun fichier ou dossier de ce type\n",
			shell->cmd->exec.args[i]);
		shell->last_error = 127;
		return ;
	}
	if (!shell->cmd->built_in && (access(shell->cmd->exec.cmd_path, X_OK)
			|| (!stat(shell->cmd->exec.cmd_path, &buf)
				&& S_ISDIR(buf.st_mode))))
	{
		printf("env: «%s»: Permission non accordée\n", shell->cmd->exec.args[i]);
		shell->last_error = 126;
	}
	else
	{
		tmp = ft_copy_tab(&shell->cmd->exec.args[i], shell);
		if (!tmp)
			return ;
		free_tab(shell->cmd->exec.args);
		shell->cmd->exec.args = tmp;
		exec_cmd(shell);
	}
}

void	ft_env(t_shell *shell)
{
	t_env		*lst;
	int			i;
	char		**tmp;
	struct stat	buf;

	tmp = NULL;
	i = 1;
	while (shell->cmd->exec.args[i])
	{
		if (ft_strncmp(shell->cmd->exec.args[i], "env", 4) != 0)
		{
			ft_change_var(shell, i);
			ft_exec_cmd(shell, i, tmp, buf);
			return ;
		}
		i++;
	}
	lst = shell->env;
	while (lst)
	{
		printf("%s\n", lst->str);
		lst = lst->next;
	}
	shell->last_error = 0;
}
