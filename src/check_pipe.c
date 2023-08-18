/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:40:39 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 14:53:22 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe(char *str, char **tab)
{
	int	i;
	int	count;
	int	line_count;

	line_count = 0;
	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	i = 0;
	while (tab && tab[i++])
		line_count++;
	if (count == line_count - 1 || count == 0)
		return (0);
	else
		return (1);
}
