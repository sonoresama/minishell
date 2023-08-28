/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:28:30 by bastien           #+#    #+#             */
/*   Updated: 2023/08/28 16:28:34 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**parsing_path(t_shell *shell)
{
	char	*path;
	char	**split;
	t_env	*lst;

	split = NULL;
	lst = shell->env;
	while (lst && ft_strncmp("PATH", lst->name, 4))
		lst = lst->next;
	if (lst)
	{
		path = ft_strdup(lst->value);
		if (!path)
		{
			shell->error = MALLOC_ERROR;
			return (NULL);
		}
		split = ft_split(path, ':');
		free(path);
		if (!split)
		{
			shell->error = MALLOC_ERROR;
			return (NULL);
		}
	}
	return (split);
}

char	*path_cmd(char *cmd_name, t_shell *shell, int i)
{
	char	**path;
	char	*path_cmd;

	path = parsing_path(shell);
	if (!path && shell->error == MALLOC_ERROR)
		return (NULL);
	if (!path || !cmd_name || !cmd_name[0])
		return (ft_strdup(cmd_name));
	while (path[++i])
	{
		path_cmd = join_three(path[i], "/", cmd_name);
		if (!path_cmd || !access(path_cmd, F_OK | X_OK))
		{
			ft_free_tab(path);
			if (!path_cmd)
				return (NULL);
			else
				return (path_cmd);
		}
		free(path_cmd);
	}
	ft_free_tab(path);
	return (ft_strdup(cmd_name));
}
