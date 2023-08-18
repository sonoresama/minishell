/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 15:17:04 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig_handle = 0;

void	sig_handler(int signum)
{
	int	tmp;

	if (signum == SIGINT)
	{
		printf("\n");
		if (g_sig_handle > 10)
		{
			tmp = g_sig_handle;
			g_sig_handle = 1;
			kill(tmp, SIGQUIT);
		}
		else
		{
			g_sig_handle = 1;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if ((signum == SIGQUIT || signum == SIGTSTP))
	{
		if (g_sig_handle > 10 && signum == SIGQUIT)
		{
			write(2, "Quitter (core dumped)\n", 22);
			tmp = g_sig_handle;
			g_sig_handle = 2;
			kill(tmp, SIGQUIT);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*str;
	struct sigaction sa;
	t_parsing	*parsing;

	(void)argc;
	(void)argv;
	parsing = NULL;
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
		if (g_sig_handle > 0)
		{
			if (g_sig_handle == 1)
				shell->last_error = 130;
			if (g_sig_handle == 2)
				shell->last_error = 131;
			g_sig_handle = 0;
		}
		if (str == NULL)
			ft_exit(shell);
		if (!str[0] || !ft_thereisprint(str))
			continue;
		if (ft_parsing(shell, &str, &parsing) == -1)
		{
			ft_clear_parsing(parsing);
			free(str);
			write(2, "Erreur de syntaxe.\n", 19);
			shell->last_error = 2;
			continue;
		}
		ft_clear_parsing(parsing);
		free(str);
		if (shell->error == MALLOC_ERROR)
		{
			write(2, "Espace mémoire insuffisant.\n", 28);
			ft_clear_shell(shell);
			exit(0);
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
