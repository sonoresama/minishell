/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:02:42 by bastien           #+#    #+#             */
/*   Updated: 2023/05/19 11:50:21 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
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

char	*ft_strndup(char *str, unsigned int n)
{
	char	*dup;
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(str);
	if (len > n)
		len = n;
	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (str && str[i] && i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*src;
	size_t	i;

	i = 0;
	src = s;
	while (i < n)
	{
		src[i] = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
