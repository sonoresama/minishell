/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:50:22 by bastien           #+#    #+#             */
/*   Updated: 2023/08/31 10:28:42 by bastien          ###   ########.fr       */
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
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			if (g_sig_handle == 10)
				rl_redisplay();
			g_sig_handle = 1;
		}
	}
}

void	sig_handler_sigstp(int signum)
{
	if (signum == SIGTSTP)
	{
		rl_on_new_line();
		rl_redisplay();
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
		else if (g_sig_handle == 10)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
			rl_on_new_line();
	}
}

void	init_sig_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_stp;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sig_handler_sigint;
	sa_stp.sa_handler = sig_handler_sigstp;
	sa_quit.sa_handler = sig_handler_sigquit;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_stp.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_stp.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGTSTP, &sa_stp, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
