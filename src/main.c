/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/08/28 14:55:01 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig_handle = 0;

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
