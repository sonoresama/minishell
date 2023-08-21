/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:05:59 by bastien           #+#    #+#             */
/*   Updated: 2023/08/21 15:56:11 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_last_error(t_shell *shell)
{
	if (g_sig_handle > 0)
	{
		if (g_sig_handle == 1)
			shell->last_error = 130;
		if (g_sig_handle == 2)
			shell->last_error = 131;
		g_sig_handle = 0;
	}
}

static void	main_loop_part2(t_shell *shell, t_parsing *parsing, char *str)
{
	ft_clear_parsing(parsing);
	free(str);
	if (shell->error == MALLOC_ERROR)
	{
		write(2, "Espace mémoire insuffisant.\n", 30);
		ft_clear_shell(shell);
		exit(0);
	}
}

void	main_loop(t_shell *shell, char *str, t_parsing *parsing)
{
	while (1)
	{
		shell->error = 0;
		str = readline(" \033[36m\033[1mMinishell \033[33m➜ \033[0m\033[K");
		update_last_error(shell);
		if (str == NULL)
			ft_exit(shell);
		if (!str[0] || !ft_thereisprint(str))
			continue ;
		if (ft_parsing(shell, &str, &parsing) == -1)
		{
			ft_clear_parsing(parsing);
			free(str);
			write(2, "Erreur de syntaxe.\n", 19);
			shell->last_error = 2;
			continue ;
		}
		main_loop_part2(shell, parsing, str);
		if (!shell->cmd)
			continue ;
		ft_cmd(shell);
		if (shell->error == MALLOC_ERROR)
		{
			write(2, "Espace mémoire insuffisant.\n", 30);
			ft_clear_shell(shell);
			exit(0);
		}
		if (shell->last_error >= 256)
			shell->last_error = WEXITSTATUS(shell->last_error);
		update_last_error(shell);
	}
}
