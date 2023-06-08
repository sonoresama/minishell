/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:47:25 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/23 17:15:33 by bastien          ###   ########.fr       */
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

char	*path_cmd(char *cmd_name, t_shell *shell)
{
	int		i;
	char	**path;
	char	*path_cmd;

	if (!access(cmd_name, F_OK | X_OK))
		return (cmd_name);
	path = parsing_path(shell);
	if (!path)
		return (NULL);
	i = -1;
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
	return (NULL);
}