/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:08 by blerouss          #+#    #+#             */
/*   Updated: 2023/06/26 18:27:48 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_heredoc(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if ((i == 0 || str[i - 1] == ' ')
			&& str[i] == '<' && str[i + 1] == str[i]
			&& str[i + 2 == ' '])
			count++;
		i++;
	}
	return (count);
}

int	ft_thereisprint(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (1);
		i++;
	}
	return (0);
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