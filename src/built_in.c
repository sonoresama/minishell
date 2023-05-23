/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:40:59 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/23 10:26:46 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	(void)shell;
	pwd = malloc(PATH_MAX);
	if (!pwd)
		return (-1);
	getcwd(pwd, PATH_MAX);
	printf("%s\n", pwd);
	free(pwd);
	return (FT_PWD);
}

int	ft_exit(t_shell *shell)
{
//	int	sortie;
	t_cmd	*cmd;

//	sortie = 0;
	cmd = shell->cmd;
//	if (cmd->exec.args && cmd->exec.args[1])
//		sortie = ft_atoi(cmd->exec.args[1]);
	free(cmd->exec.cmd_path);
	ft_free_tab(cmd->exec.args);
	rl_clear_history();
	printf("exit\n");
	exit(0);
	return (FT_EXIT);
}

int	ft_env(t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	while (lst)
	{
		printf("%s\n",lst->str);
		lst = lst->next;
	}
	return (FT_ENV);
}

int	ft_cd(t_shell *shell)
{
	if (chdir(shell->cmd->exec.args[1]) != 0)
	{
		perror("cd ");
		return (-1);
	}
	return (FT_CD);
}
