/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:47:25 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/12 18:46:04 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	split = ft_split(path, ":");
	if (!split)
		return (NULL);
	split[0] = split[0] + ft_strlen("PATH=");
	free(path);
	return (split);
}

char	**check(char **env)
{
	char	**path;

	path = parsing_path(env);
	if (!path)
		error_msg(1, "Split");
	return (path);
}

char	*path_cmd(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*path_cmd;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	path = check(env);
	i = -1;
	while (path[++i])
	{
		path_cmd = join_three(path[i], "/", cmd);
		if (!path_cmd)
			error_msg(1, "Join");
		if (!access(path_cmd, F_OK | X_OK))
		{
			path[0] = path[0] - ft_strlen("PATH=");
			free_split(path);
			return (path_cmd);
		}
		free(path_cmd);
	}
	path[0] = path[0] - ft_strlen("PATH=");
	free_split(path);
	return (NULL);
}
