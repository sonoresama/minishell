/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:57:06 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 11:57:15 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*ft_fill_shell(char **env)
{
	t_shell	*shell;

	shell = ft_init_shell();
	if (!shell)
		return (NULL);
	shell->env = ft_fill_env(env, 0);
	shell->export = ft_fill_env(env, 0);
	if (!shell->env || !shell->export)
	{
		ft_clear_shell(shell);
		return (NULL);
	}
	update_env(shell);
	shell->pipein = 0;
	shell->pipeout = 1;
	shell->fd_stdin = dup(0);
	shell->fd_stdout = dup(1);
	return (shell);
}
