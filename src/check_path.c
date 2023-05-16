/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:47:25 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/16 16:13:12 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**parsing_path(char **env)
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
	split[0] = split[0] + 5;
	free(path);
	if (!split)
		perror("Unreachable PATH");
	return (split);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;	
	int		j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

static char	*join_three(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*join;

	str = ft_strjoin(s1, s2);
	if (!str)
	{
		perror("Allocation error");
		return (NULL);
	}
	join = ft_strjoin(str, s3);
	if (!join)
	{
		perror("Allocation error");
		return (NULL);
	}
	free(str);
	return (join);
}

char	*path_cmd(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*path_cmd;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	path = parsing_path(env);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path_cmd = join_three(path[i], "/", cmd);
		if (path_cmd && !access(path_cmd, F_OK | X_OK))
		{
			path[0] = path[0] - 5;
			ft_free_tab(path);
			return (path_cmd);
		}
		if (path_cmd)
			free(path_cmd);
	}
	path[0] = path[0] - 5;
	ft_free_tab(path);
	return (NULL);
}
