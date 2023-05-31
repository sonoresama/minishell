/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/31 16:22:27 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = ft_fill_shell(env);
	if (!shell)
	{
		perror("Error :");
		return (1);
	}
	while (1)
	{
		ft_parsing(shell, \
			readline("   \033[36m\033[1mMinishell \033[33m➜ \033[0m"));
		ft_clear_cmd(shell->cmd);
	}
	ft_clear_shell(shell);
	return (0);
}
