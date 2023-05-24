/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:52:25 by bastien           #+#    #+#             */
/*   Updated: 2023/05/24 15:46:55 by blerouss         ###   ########.fr       */
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

static char	*ft_strcut(char *str, int start, int end)
{
	char	*cut;
	int		i;

	i = 0;
	cut = malloc(end - start + 1);
	if (!cut)
		return (NULL);
	while (start < end)
	{
		cut[i] = str[start];
		str[start] = '0';
		i++;
		start++;
	}
	cut[i] = '\0';
	return (cut);
}

void	ft_cut_quote_space(char *str, t_parsing *parsing, t_shell *shell)
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
				quote_add_end(&parsing->quote, ft_strcut(str, i + 1, i + j));
				if (!parsing->quote)
				{
					shell->last_error = MALLOC_ERROR;
					return ;
				}
				i += j;
			}
		}
		i++;
	}
}

static char	*join_final_str_piped(int *j, char *str_piped, t_parsing *parsing, t_shell *shell)
{
	t_quote	*qtmp;
	int	k;
	char	*tmp;

	k = 1;
	tmp = NULL;
	while (str_piped && str_piped[(*j) + k] && str_piped[(*j) + k] != str_piped[(*j)])
		k++;
	if (str_piped[(*j) + k])
	{
		str_piped[(*j)] = '\0';
		tmp = join_three(str_piped, parsing->quote->str, &str_piped[(*j) + k + 1]);
		if (!tmp)
			shell->error = MALLOC_ERROR;
		free(parsing->quote->str);
		qtmp = parsing->quote->next;
		free(parsing->quote);
		parsing->quote = qtmp;
		free(str_piped);
		(*j) += k - 2;
	}
	else
		return (str_piped);
	return (tmp);
}

void	ft_paste_quote_space(char **str_piped, t_parsing *parsing, t_shell *shell)
{
	int	i;
	int	j;

	(void)shell;
	i = 0;
	while (str_piped && str_piped[i])
	{
		j = 0;
		while (str_piped[i][j])
		{
			while (str_piped[i][j] && str_piped[i][j] != '\'' && str_piped[i][j] != '\"')
				j++;
			if (str_piped[i][j])
			{
				str_piped[i] = join_final_str_piped(&j, str_piped[i], parsing, shell);
				if (str_piped[i] == NULL)
					return ;
				j++;
			}
		}
		i++;
	}
}
