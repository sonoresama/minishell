/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:00:30 by eorer             #+#    #+#             */
/*   Updated: 2023/07/25 14:23:27 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_home(t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "HOME", 5))
			return (lst->value);
		lst = lst->next;
	}
	printf("cd: HOME n'est pas paramétré\n");
	shell->last_error = 1;
	return (NULL);
}

void	ft_cd(t_shell *shell)
{
	char	*arg;
	char	*tmp;

	if (shell->cmd->exec.args[1] && shell->cmd->exec.args[2])
	{
		printf("cd: trop d'arguments\n");
		shell->last_error = 1;
		return ;
	}
	if (!shell->cmd->exec.args[1])
		arg = get_home(shell);
	else
		arg = shell->cmd->exec.args[1];
	if (arg && !arg[0])
	{
		shell->last_error = 0;
		return ;
	}
	if (arg && chdir(arg) != 0)
	{
		tmp = ft_strjoin("cd: ", arg);
		perror(tmp);
		free(tmp);
		shell->last_error = 1;
		return ;
	}
	if (arg)
		shell->last_error = 0;
}
