/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/12 19:32:44 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_charnbr(char	*str, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == c)
			nbr++;
		i++;
	}
	return (nbr);
}

char	*ft_strcut(char *str, int start , int end)
{
	char	*cut;
	int	i;

	i = 0;
	cut = malloc(end - start + 1);
	while (start < end)
	{
		cut[i] = str[start];
		str[start] = '0';
		i++;
		start++;
	}
	cut[i] = '\0';
	return (cut);
}

void	ft_cut_quote(char *str, char c, char **quote)
{
	int	i;
	int	j;
	int	start;
	int	end;

	start = 0;
	end = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c && !start)
			start = i;
		if (str[i] == c && start)
		{
			end = i;
			quote[j] = ft_strcut(str, start + 1, end);
			start = 0;
			end = 0;
			j++;
		}
		i++;
	}
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	t_mini	*start;
	t_parsing	parsing;
	int	i;
	(void)argc;
	(void)argv;
	(void)env;

	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
		return (1);
	start = mini;
	while (1)
	{
		parsing.str = readline("  \033[36m\033[1mMinishell \033[33m➜ \033[0m");
	//gestion heredoc
		add_history(parsing.str);
	/*	parsing.utils = ft_charnbr(str, '\'');
		if (parsing.utils && parsing.utils % 2 == 0)
		{
			parsing.quote = malloc(sizeof(char*) * ft_charnbr(str,'\''));
			ft_cut_quote(parsing.str, '\'', parsing.quote);
		}
	// return si impaire avec erreur quote non fermee	
		parsing.utils = ft_charnbr(str, '\"');
		if (parsing.utils && parsing.utils % 2 == 0)
		{
			parsing.dquote = malloc(sizeof(char*) * ft_charnbr(str,'\"'));
			ft_cut_quote(parsing.str, '\"', parsing.dquote);
		}
	// return si impaire avec erreur quote non fermee	
	*/	parsing.str_piped = ft_split(parsing.str, '|');
		parsing.utils = 0;
		while (parsing.str_piped[parsing.utils])
		{
			parsing.cmd_line = ft_split(parsing.str_piped[parsing.utils], ' ');
			ft_free_tab(parsing.str_piped);
			if (parsing.cmd_line[0][0] != '<' && parsing.cmd_line[0][0] != '>')
				mini->args = parsing.cmd_line;
			else
			{
				i = 0;
				while (parsing.cmd_line[i + 2])
				{
					parsing.cmd_line[i] = parsing.cmd_line[i + 2];
					i++;
				}
				parsing.cmd_line[i] = NULL;
				mini->args = parsing.cmd_line;
			}
	/*		if //test access
			else if//verif built-in
			else
			{
				mini->cmd.args[0] = path_cmd(mini->cmd.args[0], env);
			}
			if (!mini->cmd.args[0])
				//free all "commande introuvable"*/
			parsing.utils++;
			if (parsing.str_piped[parsing.utils])
			{
				mini->next = malloc(sizeof(t_mini));
				mini = mini->next;
			}
		}
		mini = start;
		while (mini)
		{
			ft_print_tab(mini->args);
			ft_free_tab(mini->args);
			start = mini;
			mini = mini->next;
			free(start);
		}
		if (!strcmp(parsing.str, "exit"))
		{
			rl_clear_history();
			free(parsing.str);
			exit(0);
		}
	}
	return (0);
}
