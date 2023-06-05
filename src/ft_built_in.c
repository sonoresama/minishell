/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:41:40 by eorer             #+#    #+#             */
/*   Updated: 2023/06/05 11:45:03 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_My_func	is_built_in(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (&ft_exit);
	else if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (&ft_pwd);
	else if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (&ft_cd);
	else if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (&ft_echo);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (&ft_env);
	else if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (&ft_export);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (&ft_unset);
	else
		return (NULL);
}
