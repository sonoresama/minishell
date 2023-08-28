/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:24:53 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 16:36:21 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	write_heredoc(char *eof)
{
	int		fd;
	char	*str;

	fd = open("heredoc", O_CREAT | O_RDWR, 0666);
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
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	return (fd);
}

int	ft_heredoc(char **heredoc)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (heredoc[i])
	{
		if (fd)
		{
			if (unlink("heredoc") == -1)
			{
				perror("UNLINK");
				return (-1);
			}
			close(fd);
		}
		fd = write_heredoc(heredoc[i]);
		if (fd == -1)
			return (-1);
		i++;
	}
	close(fd);
	return (0);
}
