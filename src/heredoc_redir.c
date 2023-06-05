/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:55:56 by blerouss          #+#    #+#             */
/*   Updated: 2023/06/05 11:50:59 by emileorer        ###   ########.fr       */
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
	while (str && str[i] && !(str[i] != ' ' && str[i - 1] == ' '))
	{
		str[i] = ' ';
		i++;
	}
	str[0] = ' ';
	while (str[i + len] != ' ' && str[i + len])
		len++;
	dup = malloc(len + 1);
	dup[len] = '\0';
	while (j < len)
	{
		dup[j] = str[i + j];
		str[i + j] = ' ';
		j++;
	}	
	return (dup);
}

static void	ft_redir(t_cmd *cmd, char *str, int i)
{
	char	*dup;

	if (str[i] == '<')
	{
		if (cmd->infile > 2)
			close(cmd->infile);
		dup = ft_dup_next_word(&str[i]);
		cmd->infile = open(dup, O_RDONLY);
		if (dup)
			free(dup);
	}
	else if (str[i] == '>')
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		dup = ft_dup_next_word(&str[i]);
		cmd->outfile = open(dup, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (dup)
			free(dup);
	}
	if (cmd->outfile == -1 || cmd->infile == -1)
		perror("error");
}

static void	ft_heredoc_append(t_cmd *cmd, char *str, int i, int *j)
{
	char	*dup;

	if (str[i] == '<')
		cmd->heredoc[(*j)++] = ft_dup_next_word(&str[i]);
	else if (str[i] == '>')
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		dup = ft_dup_next_word(&str[i]);
		cmd->outfile = open(dup, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (dup)
			free(dup);
	}
	if (cmd->outfile == -1 || cmd->infile == -1)
		perror("error");
}

void	ft_fill_redir_heredoc(char *str, t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		k = double_chrcmp(&str[i], '<', '>');
		if (k == -1)
			return ;
		else
			i += k;
		if ((i == 0 || str[i - 1] == ' ') && str[i + 1] == ' ')
			ft_redir(cmd, str, i);
		else if ((i == 0 || str[i - 1] == ' ')
			&& str[i + 1] == str[i] && str[i + 2 == ' '])
			ft_heredoc_append(cmd, str, i, &j);
		i++;
	}
}
