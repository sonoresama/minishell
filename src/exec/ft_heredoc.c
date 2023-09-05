/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:24:53 by eorer             #+#    #+#             */
/*   Updated: 2023/09/05 18:18:15 by eorer            ###   ########.fr       */
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

int	write_heredoc(char *eof, char *file, t_shell *shell)
{
	int		fd;
	char	*str;

	fd = open(file, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		perror("OPEN HEREDOC");
		return (-1);
	}
	str = NULL;
	while (ft_strncmp(eof, str, ft_strlen(eof) + 1))
	{
		str = readline("heredoc>> ");
		if (!ft_strncmp(eof, str, ft_strlen(eof) + 1))
			return (fd);
		replace_var_env_in_str(&str, shell);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	return (fd);
}

int	ft_heredoc(char **heredoc, t_shell *shell)
{
	int		i;
	int		fd;
	char	*file;

	i = 0;
	fd = 0;
	file = generate_file_name();
	while (heredoc[i])
	{
		if (fd)
		{
			if (unlink(file) == -1)
				return (-1);
			close(fd);
		}
		fd = write_heredoc(heredoc[i], file, shell);
		if (fd == -1)
			return (-1);
		i++;
	}
	close(fd);
	fd = open(file, O_RDWR);
	free(file);
	return (fd);
}