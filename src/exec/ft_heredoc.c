/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:24:53 by eorer             #+#    #+#             */
/*   Updated: 2023/09/13 12:22:18 by eorer            ###   ########.fr       */
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
		if (str)
			free(str);
		g_sig_handle = 7;
		str = readline("heredoc>> ");
		if (!str)
			return (-1);
		if (!ft_strncmp(eof, str, ft_strlen(eof) + 1))
		{
			free(str);
			return (0);
		}
		replace_var_env_in_str(&str, shell);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	return (0);
}

int	ft_heredoc(char **heredoc, t_shell *shell, int i, int fd)
{
	int		std_in;
	char	*file;

	file = generate_file_name();
	std_in = dup(STDIN_FILENO);
	while (heredoc[i])
	{
		if (handle_fd_value(&fd, file, std_in) == -1)
			return (-1);
		if (write_heredoc(heredoc[i], fd, shell) == -1)
		{
			if (g_sig_handle == 6)
				return (ctrl_c_heredoc(std_in, fd, file, shell));
			else
			{
				printf("warning: here-document delimited by end-of-file (want");
				printf("ed `%s')\n", heredoc[i]);
				if (!heredoc[i + 1])
					return (ctrl_bs_heredoc(std_in, fd, file, shell));
			}
		}
		i++;
	}
	return (setup_end_function(std_in, fd, file));
}
