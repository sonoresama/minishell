/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:48:55 by blerouss          #+#    #+#             */
/*   Updated: 2023/09/11 18:24:18 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ctrl_c_heredoc(int std_in, int fd, char *file, t_shell *shell)
{
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	close(fd);
	free(file);
	shell->error = 5;
	g_sig_handle = 1;
	return (-1);
}

int	ctrl_bs_heredoc(int std_in, int fd, char *file, t_shell *shell)
{
	close(std_in);
	shell->last_error = 0;
	shell->error = 5;
	free(file);
	return (fd);
}

int	handle_fd_value(int *fd, char *file, int std_in)
{
	if ((*fd) && (*fd) != -1)
	{
		close((*fd));
		if (unlink(file) == -1)
			return (-1);
	}
	(*fd) = open(file, O_CREAT | O_RDWR, 0666);
	if ((*fd) == -1)
	{
		free(file);
		close(std_in);
		unlink_heredoc_files();
		perror("OPEN HEREDOC");
		return (-1);
	}
	return (0);
}

int	setup_end_function(int std_in, int fd, char *file)
{
	close(std_in);
	close(fd);
	fd = open(file, O_RDWR);
	free(file);
	return (fd);
}
