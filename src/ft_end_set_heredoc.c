/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_set_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:38 by bastien           #+#    #+#             */
/*   Updated: 2023/08/10 16:17:51 by bastien          ###   ########.fr       */
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
		if ((*heredoc)[i] == '$' && ((*heredoc)[i + 1] == '\'' || (*heredoc)[i + 1] == '"'))
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

static char	*ft_paste_quote(char **heredoc, t_quote **tmpq, int *i)
{
	char	*tmp;

	(*heredoc)[(*i)++] = '\0';
	while ((*heredoc)[(*i)] != '"' && (*heredoc)[(*i)] != '\'')
		(*i)++;
	tmp = join_three((*heredoc), (*tmpq)->str, &(*heredoc)[1 + (*i)--]);
	free((*heredoc));
	(*tmpq) = (*tmpq)->next;
	return (tmp);
}

void	ft_end_set_heredoc(t_quote *tmpd, t_quote *tmpq, char **heredoc, t_shell *shell)
{
	int		i;

	i = 0;
	replace_var_env_in_heredoc(heredoc, shell);
	if (shell->error == MALLOC_ERROR)
		return ;
	while ((*heredoc) && (*heredoc)[i])
	{
		if ((*heredoc)[i] == '"')
			(*heredoc) = ft_paste_quote(heredoc, &tmpd, &i);
		else if ((*heredoc)[i] == '\'')
			(*heredoc) = ft_paste_quote(heredoc, &tmpq, &i);
		else
			i++;
	}
}
