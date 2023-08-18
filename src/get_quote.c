/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:06:34 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 17:40:27 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_quote	*get_dquote(char *str, int n, t_parsing *parsing)
{
	t_quote	*tmpd;
	int		i;

	tmpd = parsing->dquote;
	i = 0;
	while (i < n)
	{
		if (str[i] == '"')
		{
			tmpd = tmpd->next;
			i++;
			while (str[i] != '"')
				i++;
		}
		i++;
	}
	return (tmpd);
}

t_quote	*get_quote(char *str, int n, t_parsing *parsing)
{
	t_quote	*tmpq;
	int		i;

	tmpq = parsing->quote;
	i = 0;
	while (i < n)
	{
		if (str[i] == '\'')
		{
			tmpq = tmpq->next;
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (tmpq);
}
