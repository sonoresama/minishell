/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:47:25 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/19 17:15:14 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (NULL);
	join = ft_strjoin(str, s3);
	if (!join)
		return (NULL);
	free(str);
	return (join);
}

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
	split[0] = split[0] + ft_strlen("PATH=");
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
			path[0] = path[0] - ft_strlen("PATH=");
			ft_free_tab(path);
			return (path_cmd);
		}
		free(path_cmd);
	}
	path[0] = path[0] - ft_strlen("PATH=");
	ft_free_tab(path);
	return (NULL);
}
