/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:05:12 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 17:45:46 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	ft_init_redirection(char *str, t_parsing *parsing)
{
	int	heredoc;
	int	redir;
	int	i;

	i = -1;
	heredoc = 0;
	redir = 0;
	while (str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && next_word_exist(&str[i]))
		{
			i += 2;
			heredoc++;
		}
		if ((str[i] == '<' || str[i] == '>') && next_word_exist(&str[i]))
		{
			redir++;
			while (str[i] == '<' || str[i] == '>')
				i++;
		}
	}
	parsing->heredoc = malloc(sizeof(char *) * (heredoc + 1));
	parsing->redir = malloc(sizeof(char *) * (redir + 1));
	parsing->redir[redir] = NULL;
	parsing->heredoc[heredoc] = NULL;
}

t_parsing	*ft_fill_parsing(char *str, t_parsing *parsing, t_shell *shell)
{
	parsing = malloc (sizeof(t_parsing));
	if (!parsing)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	parsing->quote = NULL;
	parsing->dquote = NULL;
	parsing->heredoc = NULL;
	parsing->redir = NULL;
	ft_init_redirection(str, parsing);
	if (!parsing->heredoc || !parsing->redir)
	{
		shell->error = MALLOC_ERROR;
		return (parsing);
	}
	return (parsing);
}
