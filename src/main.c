/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/07/03 16:27:06 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig_handle;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*str;
	struct sigaction sa;

	(void)argc;
	(void)argv;
	g_sig_handle = 0;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	shell = ft_fill_shell(env);
	if (!shell)
	{
		perror("INIT SHELL");
		return (1);
	}
	while (1)
	{
		shell->error = 0;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		str = readline(" \033[36m\033[1mMinishell \033[33m➜ \033[0m");
		if (!str || !str[0] || !ft_thereisprint(str))
			continue;
		if (ft_parsing(shell, str) == -1)
		{
			printf("erreur de syntaxe\n");
			shell->last_error = 2;
			continue;
		}
		ft_cmd(shell);
		if (shell->last_error > 256)
			shell->last_error = WEXITSTATUS(shell->last_error);
		ft_clear_cmd(shell->cmd);
		shell->cmd = NULL;
	//	if (g_sig_handle = 1)
		//ft_exit(shell);
	}
	return (0);
}
