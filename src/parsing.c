/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:48:36 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:04:17 by eorer            ###   ########.fr       */
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

char	**parsing_path(char **env)
{
	char	*path;
	char	**split;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp("PATH", env[i], 4))
		i++;
	if (env[i])
		path = ft_strdup(env[i]);
	else
		return (NULL);
	split = ft_split(path, ':');
	if (!split)
		return (NULL);
	split[0] = split[0] + ft_strlen("PATH=");
	free(path);
	return (split);
}

char	**check(char **env, t_cmd *cmd)
{
	char	**path;

	path = parsing_path(env);
	if (!path)
	{
		free_tab(cmd->exec.args);
		perror("ERREUR ");
	}
	return (path);
}

char	*path_cmd(char *cmd, char **env, t_cmd *cmd)
{
	int		i;
	char	**path;
	char	*path_cmd;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	path = check(env, cmd);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path_cmd = join_three(path[i], "/", cmd);
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
