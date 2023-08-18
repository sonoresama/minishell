/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_chrcmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:13:30 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 18:21:36 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	next_word_exist(char *str)
{
	int		i;

	i = 1;
	if (str[0] == str[1])
		i++;
	while (str && str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	if (!str[i] || str[i] == '<' || str[i] == '>')
		return (0);
	return (1);
}

int	double_chrcmp(char *str, char c, char d)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c && str[i] != d)
		i++;
	if (!str[i])
		return (-1);
	if (!next_word_exist(&str[i]))
		return (-2);
	return (i);
}
