/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:28:22 by eorer             #+#    #+#             */
/*   Updated: 2023/07/31 17:35:41 by bastien          ###   ########.fr       */
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
		printf("pwd: erreur de détermination du répertoire actuel : ");
		printf("getcwd : ne peut accéder aux répertoires parents : Au");
		printf("cun fichier ou dossier de ce type\n");
		shell->last_error = 1;
	}
	else
	{
		printf("%s\n", pwd);
		shell->last_error = 0;
	}
	free(pwd);
}
