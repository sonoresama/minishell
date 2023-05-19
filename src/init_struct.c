/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:21:01 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/19 17:24:46 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*ft_init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("Allocation error : ");
		exit(1);
	}
	ft_bzero(shell, sizeof(t_shell));
	return (shell);
}

t_env	*ft_init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		perror("Allocation error : ");
		exit(1);
	}
	ft_bzero(env, sizeof(t_env));
	return (env);
}

t_cmd	*ft_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		perror("Allocation error : ");
		exit(1);
	}
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}
