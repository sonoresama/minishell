/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emileorer <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:55:36 by emileorer         #+#    #+#             */
/*   Updated: 2023/07/03 14:41:07 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env_export(t_shell *shell)
{
	t_env	*env;

	env = shell->export;
	while (env)
	{
		printf("export ");
		printf("%s\n", env->str);
		env = env->next;
	}
}
