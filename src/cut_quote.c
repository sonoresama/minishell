/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:52:25 by bastien           #+#    #+#             */
/*   Updated: 2023/07/22 14:46:29 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_quote	*quote_last(t_quote *lst)
{
	t_quote	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	quote_add_end(t_quote **lst, char *str)
{
	t_quote	*last;

	if (!str)
		return ;
	if (*lst)
	{
		last = quote_last(*lst);
		last->next = malloc(sizeof(t_quote));
		if (!last->next)
		{
			ft_clear_quote(lst);
			return ;
		}
		last->next->str = str;
		last->next->next = NULL;
	}
	else
	{
		(*lst) = malloc(sizeof(t_quote));
		if (!(*lst))
			return ;
		(*lst)->str = str;
		(*lst)->next = NULL;
	}
}

static int	ft_cut_quote_space_bis(char *str, int *i, int j, t_parsing *parsing)
{
	if (str[(*i)] == '\'')
		quote_add_end(&parsing->quote, ft_strcut(str, (*i) + 1, (*i) + j));
	else if (str[(*i)] == '\"')
		quote_add_end(&parsing->dquote, ft_strcut(str, (*i) + 1, (*i) + j));
	if (!parsing->quote && !parsing->dquote)
		return (1);
	(*i) += j;
	return (0);
}

int	ft_cut_quote_space(char *str, t_parsing *parsing, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 1;
		if (str[i] == '\'' || str[i] == '\"')
		{
			while (str[i + j] && str[i + j] != str[i])
				j++;
			if (str[i + j])
			{
				if (ft_cut_quote_space_bis(str, &i, j, parsing))
					return (shell->error = MALLOC_ERROR);
			}
			else
				return (shell->error = SYNTAX_ERROR);
		}
		i++;
	}
	return (0);
}
