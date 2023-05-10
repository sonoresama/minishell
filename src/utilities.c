/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:04:33 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 16:16:52 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau && tableau[i])
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return(i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int	i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (*s1 == *s2 && *s1 && *s2 && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	return (*s1 - *s2);
}

