/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:38:42 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = malloc(PATH_MAX);
	if (!pwd)
		return (-1);
	getcwd(pwd, PATH_MAX);
	printf("%s\n", pwd);
	free(pwd);
	return (FT_PWD);
}

int	ft_exit(t_cmd *cmd)
{
	int	sortie;

	sortie = 0;
	if (cmd->exec.args && cmd->exec.args[1])
		sortie = ft_atoi(cmd->exec.args[1]);
	free(cmd->exec.cmd_path);
	free_tab(cmd->exec.args);
	rl_clear_history();
	printf("exit\n");
	exit(FT_EXIT);
	return (FT_EXIT);
}

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env && cmd->env[i])
	{
		printf("%s\n",cmd->env[i]);
		i++;
	}
	return  (FT_ENV);
}

int	ft_cd(t_cmd *cmd)
{
	if (chdir(cmd->exec.args[1]) != 0)
	{
		perror("cd ");
		return (-1);
	}
	return (FT_CD);
}
