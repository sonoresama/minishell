/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 16:18:47 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pwd(char *cwd)
{
	char	*pwd;

	if (cwd)
		free(cwd);
	pwd = malloc(PATH_MAX);
	if (!pwd)
		return (NULL);
	getcwd(pwd, PATH_MAX);
	printf("%s\n", pwd);
	return (pwd);
}

void	ft_exit(t_mini *mini)
{
	int	sortie;

	sortie = 0;
	if (mini->args && mini->args[0]){
		sortie = ft_atoi(mini->args[0]);
		printf("GOOD\n");}
	free(mini->cmd);
	free_tab(mini->args - 1);
	rl_clear_history();
	printf("exit\n");
	exit(sortie);
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

int	ft_cd(const char *path)
{
	if (chdir(path) != 0)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}
