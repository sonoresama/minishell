/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/05/05 18:58:59 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = malloc(10000);
	if (!pwd)
		return ;
	getcwd(pwd, 1000);
	printf("%s\n", pwd);
	free(pwd);
	return ;
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}
