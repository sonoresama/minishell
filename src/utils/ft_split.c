/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:00:37 by eorer             #+#    #+#             */
/*   Updated: 2023/08/24 18:00:53 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	size_tab(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			while (*str != c && *str)
				str++;
			count = count + 1;
		}
		else
			str++;
	}
	return (count);
}

static char	**ft_alloc(char *str, char c, char **tableau)
{
	int	count;
	int	i;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			i = 0;
			while ((*str) && (*str) != c)
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

static void	ft_implementation(char *str, char c, char **tableau)
{
	int	pos;
	int	i;
	int	j;

	pos = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			j = 0;
			while (str[i + j] != c && str[i + j])
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

char	**ft_split(const char *s, char c)
{
	char	**tableau;
	int		size;

	size = size_tab((char *)s, c);
	tableau = malloc(sizeof(tableau) * (size + 1));
	if (!tableau)
		return (NULL);
	if (ft_alloc((char *)s, c, tableau) == NULL)
	{
		ft_free_tab(tableau);
		return (NULL);
	}
	ft_implementation((char *)s, c, tableau);
	tableau[size] = NULL;
	return (tableau);
}
