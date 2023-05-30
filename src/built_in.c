/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/05/06 17:43:18 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pwd(void)
{
	char	*pwd;

	pwd = malloc(10000);
	if (!pwd)
		return (NULL);
	getcwd(pwd, 1000);
	return (pwd);
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/*void	ft_echo(t_mini *mini)
{
	printf("%s", mini->arg);
	if (mini->option == 'n')
		return;
	printf("\n");
}*/
