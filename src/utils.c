/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:08:50 by eorer             #+#    #+#             */
/*   Updated: 2023/05/04 18:12:37 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	get_exec(char **env)
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
