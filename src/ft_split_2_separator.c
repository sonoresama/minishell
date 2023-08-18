/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2_separator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:00:37 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 12:05:49 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	size_tab(char *str, char c, char d)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != c && *str != d)
		{
			while (*str != c && *str != d && *str)
				str++;
			count++;
		}
		else
			str++;
	}
	return (count);
}

static char	**ft_alloc(char *str, char c, char d, char **tableau)
{
	int	count;
	int	i;

	count = 0;
	while (*str)
	{
		if (*str != c && *str != d)
		{
			i = 0;
			while (*str != c && *str != d && *str)
			{
				i++;
				str++;
			}
			tableau[count] = malloc(i + 1);
			if (!tableau[count])
				return (NULL);
			count++;
		}
		else
			str++;
	}
	return (tableau);
}

static void	ft_implementation(char *str, char c, char d, char **tableau)
{
	int	pos;
	int	i;
	int	j;

	pos = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != d)
		{
			j = 0;
			while (str[i + j] != c && str[i + j] != d && str[i + j])
			{
				tableau[pos][j] = str[i + j];
				j++;
			}
			tableau[pos][j] = '\0';
			pos++;
			i = i + j;
		}
		else
			i++;
	}
}

char	**ft_split_2_separator(const char *s, char c, char d)
{
	char	**tableau;
	int		size;

	size = size_tab((char *)s, c, d);
	tableau = malloc(sizeof(tableau) * (size + 1));
	if (tableau == 0)
		return (0);
	if (ft_alloc((char *)s, c, d, tableau) == NULL)
	{
		ft_free_tab(tableau);
		return (NULL);
	}
	ft_implementation((char *)s, c, d, tableau);
	tableau[size] = NULL;
	return (tableau);
}
