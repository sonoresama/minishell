/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:47:25 by blerouss          #+#    #+#             */
/*   Updated: 2023/07/22 13:26:49 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**parsing_path(t_shell *shell)
{
	char	*path;
	char	**split;
	t_env	*lst;

	lst = shell->env;
	while (lst && ft_strncmp("PATH", lst->name, 4))
		lst = lst->next;
	if (lst)
		path = ft_strdup(lst->value);
	else
		return (NULL);
	split = ft_split(path, ':');
	if (!split)
		return (NULL);
	free(path);
	return (split);
}

char	*path_cmd(char *cmd_name, t_shell *shell, int i)
{
	char	**path;
	char	*path_cmd;

	if (!cmd_name)
		return (NULL);
	if (!access(cmd_name, F_OK | X_OK) || cmd_name[0] == '\0')
		return (ft_strdup(cmd_name));
	path = parsing_path(shell);
	if (!path)
		return (NULL);
	while (path[++i])
	{
		path_cmd = join_three(path[i], "/", cmd_name);
		if (!path_cmd)
			perror("ERREUR ");
		if (!access(path_cmd, F_OK | X_OK))
		{
			ft_free_tab(path);
			return (path_cmd);
		}
		free(path_cmd);
	}
	ft_free_tab(path);
	return (ft_strdup(cmd_name));
}
