/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 15:41:01 by blerouss         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	(void)argc;
	(void)argv;
	while (1)
	{
		shell = ft_parsing(env, readline("  \033[36m\033[1mMinishell \033[33m➜ \033[0m"));
//		if (cmd->env && cmd->env->value)
//			printf("str = %s\nname = %s\nvalue =%s\n", cmd->env->str, cmd->env->name, cmd->env->value);
		ft_clear_shell(shell); 
	}
	return (0);
}
