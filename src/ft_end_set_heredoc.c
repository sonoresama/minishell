/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_set_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:38 by bastien           #+#    #+#             */
/*   Updated: 2023/08/24 18:29:04 by bastien          ###   ########.fr       */
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

static char	*ft_paste_quote(char **heredoc, t_quote **tmpq, int *i, t_shell *shell)
{
	char	*tmp;

	(*heredoc)[(*i)++] = '\0';
	while ((*heredoc)[(*i)] != '"' && (*heredoc)[(*i)] != '\'')
		(*i)++;
	tmp = join_three((*heredoc), (*tmpq)->str, &(*heredoc)[1 + (*i)--]);
	if (!tmp)
		shell->error = MALLOC_ERROR;
	free((*heredoc));
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
			(*hdoc) = ft_paste_quote(hdoc, &tmpd, &i, shell);
		else if ((*hdoc)[i] == '\'')
			(*hdoc) = ft_paste_quote(hdoc, &tmpq, &i, shell);
		else
			i++;
		if (shell->error == MALLOC_ERROR)
			return ;
	}
}
