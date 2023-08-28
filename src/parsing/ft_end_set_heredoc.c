/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_set_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:38 by bastien           #+#    #+#             */
/*   Updated: 2023/08/28 16:04:27 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	replace_var_env_in_heredoc(char **heredoc, t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*heredoc) && (*heredoc)[i])
	{
		if ((*heredoc)[i] == '$' && ((*heredoc)[i + 1] == '\''
				|| (*heredoc)[i + 1] == '"'))
		{
			(*heredoc)[i] = '\0';
			tmp = ft_strjoin((*heredoc), &(*heredoc)[i + 1]);
			if (!tmp)
				shell->error = MALLOC_ERROR;
			free((*heredoc));
			(*heredoc) = tmp;
		}
		if ((*heredoc)[i] == '$' && (*heredoc)[i + 1] == '$')
			i++;
		i++;
	}
}

static char	*ft_paste_quote(char **here, t_quote **tmpq, int *i, t_shell *sh)
{
	char	*tmp;

	(*here)[(*i)++] = '\0';
	while ((*here)[(*i)] != '"' && (*here)[(*i)] != '\'')
		(*i)++;
	tmp = join_three((*here), (*tmpq)->str, &(*here)[1 + (*i)--]);
	if (!tmp)
		sh->error = MALLOC_ERROR;
	free((*here));
	(*tmpq) = (*tmpq)->next;
	return (tmp);
}

void	ft_end_set_hdoc(t_quote *tmpd, t_quote *tmpq, char **hdoc, t_shell *sh)
{
	int		i;

	i = 0;
	replace_var_env_in_heredoc(hdoc, sh);
	if (sh->error == MALLOC_ERROR)
		return ;
	while ((*hdoc) && (*hdoc)[i])
	{
		if ((*hdoc)[i] == '"')
			(*hdoc) = ft_paste_quote(hdoc, &tmpd, &i, sh);
		else if ((*hdoc)[i] == '\'')
			(*hdoc) = ft_paste_quote(hdoc, &tmpq, &i, sh);
		else
			i++;
		if (sh->error == MALLOC_ERROR)
			return ;
	}
}
