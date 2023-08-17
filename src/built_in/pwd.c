/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:28:22 by eorer             #+#    #+#             */
/*   Updated: 2023/08/10 18:00:48 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	(void)shell;
	pwd = malloc(PATH_MAX);
	if (!pwd)
	{
		shell->last_error = 1;
		return ;
	}
	pwd[0] = '\0';
	getcwd(pwd, PATH_MAX);
	if (!pwd[0])
	{
		write(2, "pwd: erreur de détermination du répertoire actuel : ", 55);
		write(2, "getcwd : ne peut accéder aux répertoires parents : Au", 56);
		write(2, "cun fichier ou dossier de ce type\n", 34);
		shell->last_error = 1;
	}
	else
	{
		printf("%s\n", pwd);
		shell->last_error = 0;
	}
	free(pwd);
}
