/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/08/30 16:11:11 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig_handle = 10;

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	char		*str;
	t_parsing	*parsing;

	(void)argc;
	(void)argv;
	parsing = NULL;
	str = NULL;
	init_sig_handler();
	shell = ft_fill_shell(env);
	if (!shell || shell->error == MALLOC_ERROR)
	{
		ft_clear_shell(shell);
		write(2, "Espace mémoire insuffisant.\n", 30);
		return (1);
	}
	main_loop(shell, str, parsing);
	return (0);
}
