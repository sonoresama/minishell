/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:55:56 by blerouss          #+#    #+#             */
/*   Updated: 2023/08/03 17:45:37 by bastien          ###   ########.fr       */
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
	while (str && str[i] && (str[i] == ' ' || str[i] == '	'))
	{
		str[i] = ' ';
		i++;
	}
	str[0] = ' ';
	while (str[i + len] && str[i + len] != ' ' && str[i + len] != '<' && str[i + len] != '>')
		len++;
	dup = malloc(len + 1);
	//protection malloc
	dup[len] = '\0';
	while (j < len)
	{
		dup[j] = str[i + j];
		str[i + j] = ' ';
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

static void	ft_redir(t_cmd *cmd, char *str, int i, t_shell *shell)
{
	char	*dup;

	if (str[i] == '<')
	{
		if (cmd->infile > 2)
			close(cmd->infile);
		dup = ft_dup_next_word(&str[i]);
		cmd->infile = open(dup, O_RDONLY);
		if (cmd->infile == -1)
		{
			shell->error = REDIR_ERROR;
			shell->last_error = 1;
			perror(dup);
		}
		if (dup)
			free(dup);
	}
	else if (str[i] == '>')
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		dup = ft_dup_next_word(&str[i]);
		cmd->outfile = open(dup, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (cmd->outfile == -1)
			perror(dup);
		if (dup)
			free(dup);
	}
}

static void	ft_heredoc_append(t_cmd *cmd, char *str, int i, int *j)
{
	char	*dup;

	if (str[i] == '<')
	{
		if (cmd->infile > 2)
			close(cmd->infile);
		cmd->infile = -3;
		cmd->heredoc[(*j)++] = ft_dup_next_word(&str[i + 1]);
		str[i] = ' ';
	}
	else if (str[i] == '>')
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		dup = ft_dup_next_word(&str[i + 1]);
		str[i] = ' ';
		cmd->outfile = open(dup, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (cmd->outfile == -1)
			perror(dup);
		if (dup)
			free(dup);
	}
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

int	ft_fill_redir_heredoc(char *str, t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (str && str[i])
	{
		k = double_chrcmp(&str[i], '<', '>');
		if (k == -1)
			return (0);
		if (k == -2)
			return (1);
		i += k;
		if (str[i + 1] == str[i])
			ft_heredoc_append(cmd, str, i, &j);
		else
			ft_redir(cmd, str, i, shell);
		if (shell->error == REDIR_ERROR)
			return (1);
		i++;
	}
	return (0);
}
