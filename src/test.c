/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 16:58:50 by bastien          ###   ########.fr       */
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

//int	ft_is_builtin()


int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	t_mini	*start;

	(void)argc;
	(void)argv;
	while (1)
	{
		ft_init_mini(&mini, &start);
		ft_parsing(mini, start, env);
	}
	return (0);
}
