/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_set_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:16:28 by bastien           #+#    #+#             */
/*   Updated: 2023/08/28 16:05:21 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_paste_quote(char **red, t_quote **tmpq, int *i, t_shell *sh)
{
	char	*tmp;

	(*red)[(*i)++] = '\0';
	while ((*red)[(*i)] != '"' && (*red)[(*i)] != '\'')
		(*i)++;
	tmp = join_three((*red), (*tmpq)->str, &(*red)[1 + (*i)--]);
	if (!tmp)
		sh->error = MALLOC_ERROR;
	free((*red));
	(*tmpq) = (*tmpq)->next;
	return (tmp);
}

void	ft_end_set_red(t_quote *tmpd, t_quote *tmpq, char **redir, t_shell *sh)
{
	int		i;

	i = 0;
	replace_var_env_in_str(redir, sh);
	if (sh->error == MALLOC_ERROR)
		return ;
	while ((*redir) && (*redir)[i])
	{
		if ((*redir)[i] == '"')
		{
			replace_var_env_in_str(&tmpd->str, sh);
			if (sh->error == MALLOC_ERROR)
				return ;
			(*redir) = ft_paste_quote(redir, &tmpd, &i, sh);
		}
		else if ((*redir)[i] == '\'')
			(*redir) = ft_paste_quote(redir, &tmpq, &i, sh);
		else
			i++;
		if (sh->error == MALLOC_ERROR)
			return ;
	}
}
