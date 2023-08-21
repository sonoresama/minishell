/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:50:22 by bastien           #+#    #+#             */
/*   Updated: 2023/08/21 14:23:42 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler_sigint(int signum)
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
}

void	sig_handler_sigquit_sigstp(int signum)
{
	int	tmp;

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

void	init_sig_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_other;

	sa_int.sa_handler = sig_handler_sigint;
	sa_other.sa_handler = sig_handler_sigquit_sigstp;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_other.sa_mask);
	sa_int.sa_flags = 0;
	sa_other.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_other, NULL);
	sigaction(SIGTSTP, &sa_other, NULL);
}
