/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:41:55 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 14:10:08 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_dup_next_word(char *str, t_shell *shell)
{
	char	*dup;
	int		i;
	int		j;
	int		len;

	len = 0;
	j = -1;
	i = 1;
	while (str && str[i] && (str[i] == ' ' || str[i] == '	'
			|| str[i] == '<' || str[i] == '>'))
		i++;
	while (str[i + len] && str[i + len] != ' ' && str[i + len] != '<'
		&& str[i + len] != '>')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	dup[len] = '\0';
	while (++j < len)
		dup[j] = str[i + j];
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

static void	ft_fill_redir(char *str, int *i, t_parsing *parsing, t_shell *shell)
{
	static int	l = 0;
	static int	j = 0;

	if ((*i) < 0)
	{
		l = 0;
		j = 0;
		return ;
	}
	if (str[(*i)] == '<' && str[(*i) + 1] == '<')
	{
		parsing->heredoc[j++] = ft_dup_next_word(&str[(*i)], shell);
		ft_end_set_heredoc(get_dquote(str, (*i), parsing),
			get_quote(str, (*i), parsing), &parsing->heredoc[j - 1], shell);
	}
	else
	{
		parsing->redir[l++] = ft_dup_next_word(&str[(*i)], shell);
		ft_end_set_redir(get_dquote(str, (*i), parsing),
			get_quote(str, (*i), parsing), &parsing->redir[l - 1], shell);
	}
	while (str[(*i)] == '<' || str[(*i)] == '>')
		(*i)++;
}

int	ft_copy_redir(char *str, t_parsing *parsing, t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str && str[i])
	{
		k = double_chrcmp(&str[i], '<', '>');
		if (k < 0)
		{
			ft_fill_redir(str, &k, parsing, shell);
			return (0);
		}
		i += k;
		ft_fill_redir(str, &i, parsing, shell);
		if (shell->error == MALLOC_ERROR)
			return (1);
	}
	return (0);
}
