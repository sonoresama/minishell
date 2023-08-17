/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:41:40 by eorer             #+#    #+#             */
/*   Updated: 2023/06/14 14:53:26 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_My_func	is_built_in(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen("exit") + 1))
		return (&ft_exit);
	else if (!ft_strncmp(str, "pwd", ft_strlen("pwd") + 1))
		return (&ft_pwd);
	else if (!ft_strncmp(str, "cd", ft_strlen("cd") + 1))
		return (&ft_cd);
	else if (!ft_strncmp(str, "echo", ft_strlen("echo") + 1))
		return (&ft_echo);
	else if (!ft_strncmp(str, "env", ft_strlen("env") + 1))
		return (&ft_env);
	else if (!ft_strncmp(str, "export", ft_strlen("export") + 1))
		return (&ft_export);
	else if (!ft_strncmp(str, "unset", ft_strlen("unset") + 1))
		return (&ft_unset);
	else
		return (NULL);
}
