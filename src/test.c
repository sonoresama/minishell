/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 17:44:49 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char		*str;
	struct t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	while (1)
	{
		str = readline("  \033[36m\033[1mMinishell \033[33m➜ \033[0m");
		add_history(str);
		ft_split(str, '|');
		//parse_line(str);
		/*if (exec(str_parsed))
		*/	
		if (!strcmp(str, "exit"))
		{
			rl_clear_history();
			free(str);
			free(mini);
			exit(0);
		}
	}
	return (0);
}
