/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/05/12 17:46:22 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*pwd;

	(void)mini;
	pwd = malloc(PATH_MAX);
	if (!pwd)
		return (-1);
	getcwd(pwd, PATH_MAX);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_exit(t_mini *mini)
{
	int	sortie;

	sortie = 0;
	if (mini->exec.args && mini->exec.args[1])
		sortie = ft_atoi(mini->exec.args[1]);
	free(mini->exec.cmd_path);
	free_tab(mini->exec.args);
	rl_clear_history();
	printf("exit\n");
	exit(sortie);
	return (0);
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

int	ft_cd(t_mini *mini)
{
	if (chdir(mini->exec.args[1]) != 0)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}
