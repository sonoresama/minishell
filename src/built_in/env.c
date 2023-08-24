/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/08/24 15:33:37 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_shell *shell)
{
	t_env		*lst;
	int			i;
	struct stat	buf;

	i = 1;
	ft_bzero(&buf, sizeof(struct stat));
	while (shell->cmd->exec.args[i])
	{
		if (ft_strncmp(shell->cmd->exec.args[i], "env", 4) != 0)
		{
			write(2, "env : bad argument\n", 19);
			shell->last_error = 127;
			return ;
		}
		i++;
	}
	lst = shell->env;
	while (lst)
	{
		printf("%s\n", lst->str);
		lst = lst->next;
	}
	shell->last_error = 0;
}
