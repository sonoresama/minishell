/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:24:53 by eorer             #+#    #+#             */
/*   Updated: 2023/09/07 15:08:13 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	recursive(char **str, int i)
{
	if (i >= 11)
		return (1);
	if (*str[i] >= 'z')
	{
		if (recursive(str, i + 1))
			return (1);
		*str[i] = 'a';
		return (0);
	}
	if (!*str[i])
		*str[i] = 'a';
	else
		*str[i] += 1;
	return (0);
}

int	unlink_heredoc_files(void)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * 11);
	if (!str)
		return (1);
	ft_bzero(str, 11);
	i = 1;
	str[0] = 'a';
	while (access(str, F_OK) == 0)
	{
		if (i > 25)
		{
			if (recursive(&str, 1))
				return (1);
			i = 0;
		}
		unlink(str);
		str[0] = 'a' + i;
		i++;
	}
	free(str);
	return (0);
}

char	*generate_file_name(void)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * 11);
	if (!str)
		return (NULL);
	ft_bzero(str, 11);
	i = 1;
	str[0] = 'a';
	while (access(str, F_OK) == 0)
	{
		if (i > 25)
		{
			if (recursive(&str, 1))
				return (NULL);
			i = 0;
		}
		str[0] = 'a' + i;
		i++;
	}
	return (str);
}

int	write_heredoc(char *eof, int fd, t_shell *shell)
{
	char	*str;

	str = NULL;
	while (ft_strncmp(eof, str, ft_strlen(eof) + 1))
	{
		g_sig_handle = 7;
		str = readline("heredoc>> ");
		if (!str)
			return (-1);
		if (!ft_strncmp(eof, str, ft_strlen(eof) + 1))
			return (0);
		replace_var_env_in_str(&str, shell);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	return (0);
}

int	ft_heredoc(char **heredoc, t_shell *shell)
{
	int		i;
	int		fd;
	int		stdin;
	char	*file;

	i = 0;
	fd = 0;
	file = generate_file_name();
	stdin = dup(STDIN_FILENO);
	while (heredoc[i])
	{
		if (fd && fd != -1)
		{
			close(fd);
			if (unlink(file) == -1)
				return (-1);
		}
		fd = open(file, O_CREAT | O_RDWR, 0666);
		if (fd == -1)
		{
			free(file);
			close(stdin);
			unlink_heredoc_files();
			perror("OPEN HEREDOC");
			return (-1);
		}
		if (write_heredoc(heredoc[i], fd, shell) == -1)
		{
			if (g_sig_handle == 6)
			{
				dup2(stdin, STDIN_FILENO);
				close(stdin);
				close(fd);
				free(file);
				shell->error = 5;
				g_sig_handle = 1;
				return (-1);
			}
			else
			{
				printf("warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", heredoc[i]);
				if (!heredoc[i + 1])
				{
					close(stdin);
					shell->last_error = 0;
					shell->error = 5;
					free(file);
					return (fd);
				}
			}
		}
		i++;
	}
	close(stdin);
	close(fd);
	fd = open(file, O_RDWR);
	free(file);
	return (fd);
}
