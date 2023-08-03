/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/08/03 18:43:43 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig_handle = 0;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (g_sig_handle > 10)
		{
			kill(g_sig_handle, SIGQUIT);
			g_sig_handle = 1;
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_sig_handle = 1;
		}
	}
	if ((signum == SIGQUIT || signum == SIGTSTP))
	{
		if (g_sig_handle > 10 && signum == SIGQUIT)
		{
			printf("Quitter (core dumped)\n");
			g_sig_handle = 2;
			kill(g_sig_handle, SIGQUIT);
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*str;
	struct sigaction sa;

	(void)argc;
	(void)argv;
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
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGTSTP, &sa, NULL);
		shell->error = 0;
		str = readline(" \033[36m\033[1mMinishell \033[33m➜ \033[0m\033[K");
		if (str == NULL)
			ft_exit(shell);
		if (!str[0] || !ft_thereisprint(str))
			continue;
		if (ft_parsing(shell, str) == -1)
		{
			printf("erreur de syntaxe\n");
			shell->last_error = 2;
			continue;
		}
		if (!shell->cmd)
			continue ;
		ft_cmd(shell);
		if (shell->last_error >= 256)
			shell->last_error = WEXITSTATUS(shell->last_error);
		ft_clear_cmd(shell->cmd);
		shell->cmd = NULL;
		if (g_sig_handle > 0)
		{
			if (g_sig_handle == 1)
				shell->last_error = 130;
			if (g_sig_handle == 2)
				shell->last_error = 131;
			g_sig_handle = 0;
		}
	}
	return (0);
}
