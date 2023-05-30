/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:18:24 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 14:51:32 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*join;

	str = ft_strjoin(s1, s2);
	if (!str)
		return (NULL);
	join = ft_strjoin(str, s3);
	if (!join)
		return (NULL);
	free(str);
	return (join);
}

char	**parsing_path(t_shell *shell)
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
	split[0] = split[0] + ft_strlen("PATH=");
	free(path);
	return (split);
}

char	**check(t_shell *shell, t_cmd *cmd)
{
	char	**path;

	path = parsing_path(shell);
	if (!path)
	{
		free_tab(cmd->exec.args);
		perror("ERREUR ");
	}
	return (path);
}

char	*path_cmd(char *cmd_name, t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	**path;
	char	*path_cmd;

	if (!access(cmd_name, F_OK | X_OK))
		return (cmd_name);
	path = check(shell, cmd);
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
			path[0] = path[0] - ft_strlen("PATH=");
			free_tab(path);
			return (path_cmd);
		}
		free(path_cmd);
	}
	path[0] = path[0] - ft_strlen("PATH=");
	free_tab(path);
	return (NULL);
}
