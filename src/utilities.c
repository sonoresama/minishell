/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:04:33 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 13:01:01 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	free(cmd->exec.cmd_path);
	free(cmd->exec.args);
}

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

char	*ft_strndup(char *str, int n)
{
	char	*dup;
	int	i;

	i = 0;
	if (n < ft_strlen(str))
		dup = malloc(n + 1);
	else
		dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str && str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;	
	int		j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
