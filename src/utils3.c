/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:08 by blerouss          #+#    #+#             */
/*   Updated: 2023/06/05 12:22:07 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_heredoc(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == ' ')
			&& str[i] == '<' && str[i + 1] == str[i]
			&& str[i + 2 == ' '])
			count++;
		i++;
	}
	return (count);
}

int	double_chrcmp(char *str, char c, char d)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c && str[i] != d)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

char	*ft_strcut(char *str, int start, int end)
{
	char	*cut;
	int		i;

	i = 0;
	cut = malloc(end - start + 1);
	if (!cut)
		return (NULL);
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
