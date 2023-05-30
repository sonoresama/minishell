/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:00:30 by eorer             #+#    #+#             */
/*   Updated: 2023/05/23 18:00:54 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_home(t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "HOME", 4))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_cd(t_shell *shell)
{
	char	*arg;

	if (!shell->cmd->exec.args[1])
		arg = get_home(shell);
	else
		arg = shell->cmd->exec.args[1];
	if (chdir(arg) != 0)
	{
		perror("cd ");
		return (-1);
	}
	return (FT_CD);
}
