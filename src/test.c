/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/11 19:26:29 by bastien          ###   ########.fr       */
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

int	main(void)
{
	struct t_mini	*mini;
	struct t_parsing	parsing;

	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
		return (1);
	while (1)
	{
		parsing.str = readline("  \033[36m\033[1mMinishell \033[33m➜ \033[0m");
		add_history(str);
		parsing.utils = ft_charnbr(str, '\'');
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
		parsing.str_piped = ft_split(parsing.str, '|');
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
