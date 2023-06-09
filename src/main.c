/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/06/09 15:19:14 by emileorer        ###   ########.fr       */
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
		perror("INIT SHELL");
		return (1);
	}
	while (1)
	{
		if (ft_parsing(shell, readline("   \033[36m\033[1mMinishell \033[33m➜ \033[0m")) == -1)
		{
			perror("PARSING ");
			exit(1);
		}
		ft_cmd(shell);
		ft_clear_cmd(shell->cmd);
		shell->cmd = NULL;
	}
	return (0);
}
