/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:55:56 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/31 16:19:49 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_chrcmp(char *str, char c, char d)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c && str[i] != d)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

static char	*ft_dup_next_word(char *str)
{
	char	*dup;
	int	i;
	int	j;
	int	len;

	len = 0;
	j = 0;
	i = 1;
	while (str && str[i] && !(str[i] != ' ' && str[i - 1] == ' '))
		i++;
	while (str[i + len] != ' ' && str[i + len])
		len++;
	dup = malloc(len + 1);
	dup[len] = '\0';
	while (j < len)
	{
		dup[j] = str[i + j];
		j++;
	}	
	return (dup);
}
static void	ft_redir(t_cmd *cmd, char *str, int i)
{
	if (str[i] == '<')
		cmd->infile = open(ft_dup_next_word(&str[i], O_RDONLY));
	else if (str[i] == '>')
		cmd->outfile = open(ft_dup_next_word(&str[i], O_RDWR | O_TRUNC | O_CREAT | S_IRUSR | S_IWUSR));
	if (cmd->outfile == -1 || cmd->infile == -1)
		perror();
}

static void	ft_heredoc_append(t_cmd *cmd, char *str, int i, int *j)
{
	if (str[i] == '<')
		cmd->heredoc[(*j)++] = ft_dup_next_word(&str[i]);
	else if (str[i] == '>')
		cmd->outfile = open(ft_dup_next_word(&str[i], O_RDWR | O_TRUNC | O_CREAT | S_IRUSR | S_IWUSR));
	if (cmd->outfile == -1 || cmd->infile == -1)
		perror();
}

void	ft_fill_redir_heredoc(char *str, t_cmd *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		i += ft_chrcmp(&str[i], '<', '>');
		if (i == -1)
		{
			cmd->heredoc = 0;
			cmd->infile = -1;
			cmd->outfile = -1;
			return ;
		}
		else if (i == 0 || str[i - 1] == ' ' && str[i + 1] == ' ')
			ft_redir(cmd, str, i);
		else if (i == 0 || str[i - 1] == ' ' && str[i + 1] == str[i] && str[i + 2 == ' '])
			ft_heredoc_append(cmd, str, i, &j);
		i++;
	}
}
