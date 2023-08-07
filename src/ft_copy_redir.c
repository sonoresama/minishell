/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:41:55 by bastien           #+#    #+#             */
/*   Updated: 2023/08/07 18:18:33 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_dup_next_word(char *str)
{
	char	*dup;
	int		i;
	int		j;
	int		len;

	len = 0;
	j = 0;
	i = 1;
	while (str && str[i] && (str[i] == ' ' || str[i] == '	' || str[i] == '<' || str[i] == '>'))
		i++;
	while (str[i + len] && str[i + len] != ' ' && str[i + len] != '<' && str[i + len] != '>')
		len++;
	dup = malloc(len + 1);
	//protection malloc
	dup[len] = '\0';
	while (j < len)
	{
		dup[j] = str[i + j];
		j++;
	}	
	return (dup);
}

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

static int	double_chrcmp(char *str, char c, char d)
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

static void	ft_init_parsing(char *str, t_parsing *parsing)
{
	int	heredoc;
	int	redir;
	int	i;

	i = 0;
	heredoc = 0;
	redir = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && next_word_exist(&str[i]))
		{
			i+=2;
			heredoc++;
		}
		if ((str[i] == '<' || str[i] == '>') && next_word_exist(&str[i]))
		{
			redir++;
			while (str[i] == '<' || str[i] == '>')
				i++;
		}
		i++;
	}
	parsing->heredoc = malloc(sizeof(char *) * (heredoc + 1));
	parsing->redir = malloc(sizeof(char *) * (redir + 1));
	parsing->redir[redir] = NULL;
	parsing->heredoc[heredoc] = NULL;
}

int	ft_copy_redir(char *str, t_parsing *parsing, t_shell *shell)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	ft_init_parsing(str, parsing);
	if (!parsing->heredoc || !parsing->redir)
	{
		shell->error = MALLOC_ERROR;
		return (1);
	}
	while (str && str[i])
	{
		k = double_chrcmp(&str[i], '<', '>');
		if (k < 0)
			return (0);
		i += k;
		if (str[i] == '<' && str[i + 1] == '<')
			parsing->heredoc[j++] = ft_dup_next_word(&str[i]);
		else
			parsing->redir[l++] = ft_dup_next_word(&str[i]);
		while (str[i] == '<' || str[i] == '>')	
			i++;
		if (shell->error == MALLOC_ERROR)
			return (1);
	}
	return (0);
}
