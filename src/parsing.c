/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/05/16 17:09:32 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_cmd(t_parsing *parsing, t_mini *mini)
{
	int	i;

	i = 0;
	parsing->cmd_line = ft_split(parsing->str_piped[parsing->utils], ' ');
	if (parsing->cmd_line[0][0] != '<' && parsing->cmd_line[0][0] != '>')
		mini->args = parsing->cmd_line;
	else
	{
		while (parsing->cmd_line[i + 2])
		{
			parsing->cmd_line[i] = parsing->cmd_line[i + 2];
			i++;
		}
		parsing->cmd_line[i] = NULL;
		mini->args = parsing->cmd_line;
	}
}

void	ft_parsing(t_mini *mini, t_mini *start, char **env)
{
	t_parsing	parsing;

	parsing.str = readline("  \033[36m\033[1mMinishell \033[33m➜ \033[0m");
	add_history(parsing.str);
	if (!strcmp(parsing.str, "exit"))
	{
		rl_clear_history();
		free(parsing.str);
		free(mini);
		exit(0);
	}
	//gestion heredoc
	//gestion quote
	parsing.str_piped = ft_split(parsing.str, '|');
	free(parsing.str);
	parsing.utils = 0;
	while (parsing.str_piped[parsing.utils])
	{
		parse_cmd(&parsing, mini);
		parsing.str = path_cmd(mini->args[0], env);
		free(mini->args[0]);
		mini->args[0] = parsing.str;
		parsing.utils++;
		if (parsing.str_piped[parsing.utils])
			ft_init_mini(&mini->next, NULL);
		mini = mini->next;
	}
	ft_free_tab(parsing.str_piped);
	ft_clear_mini(start);
}
