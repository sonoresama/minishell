/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 22:57:52 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/11 15:12:59 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_nbr_word(char *str, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != c && str[i] != '\0')
			i++;
		if (i > 0)
			k++;
		while (str[i] == c && str[i] != '\0')
			i++;
	}
	return (k);
}

static int	ft_strlen_word(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
	i++;
	return (i);
}

static char	*ft_mall(int k, int leng, char **tab)
{
	tab[k] = malloc(leng + 1);
	if (tab[k] == NULL)
	{
		while (k > -1)
		{
			free(tab[k]);
			k--;
		}
	}
	return (tab[k]);
}

static char	**ft_init_str(char *str, char c, char **tab, int i)
{
	int	leng;
	int	j;
	int	k;

	k = 0;
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] != c)
		{
			leng = ft_strlen_word(&str[i], c);
			tab[k] = ft_mall(k, leng, tab);
			if (!tab[k])
				return (tab);
			while (j < leng)
			{
				tab[k][j++] = str[i];
				i++;
			}
			tab[k++][j] = '\0';
		}
		else
			i++;
	}
	return (tab);
}	

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		a;
	int		i;

	i = 0;
	a = ft_nbr_word((char *)str, c);
	tab = malloc(sizeof(tab) * (a + 1));
	if (tab == NULL)
		return (NULL);
	tab = ft_init_str((char *)str, c, tab, i);
	tab[a] = NULL;
	return (tab);
}
