/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:50:22 by bastien           #+#    #+#             */
/*   Updated: 2023/09/07 18:38:01 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler_sigint(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		if (g_sig_handle > 10)
			g_sig_handle = 1;
		else if (g_sig_handle == 9)
			return ;
		else if (g_sig_handle == 7)
		{
			g_sig_handle = 6;
			close(STDIN_FILENO);
			unlink_heredoc_files();
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_sig_handle = 1;
		}
	}
}

void	sig_handler_sigquit(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_sig_handle > 10)
		{
			write(2, "Quitter (core dumped)\n", 22);
			g_sig_handle = 2;
		}
		else if (g_sig_handle == 10 || g_sig_handle == 7)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
			rl_on_new_line();
	}
}

void	unset_sig_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = SIG_IGN;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	init_sig_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sig_handler_sigint;
	sa_quit.sa_handler = sig_handler_sigquit;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
