/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:22:22 by eorer             #+#    #+#             */
/*   Updated: 2023/08/24 15:29:21 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	del_var_env(char *str, t_env **start)
{
	t_env	*lst;
	t_env	*tmp;

	tmp = NULL;
	lst = (*start);
	while (lst)
	{
		if (!ft_strncmp(str, lst->name, ft_strlen(lst->name)))
		{
			if (!tmp)
				(*start) = lst->next;
			else
				tmp->next = lst->next;
			free(lst->str);
			free(lst->name);
			free(lst->value);
			free(lst);
			return ;
		}
		tmp = lst;
		lst = lst->next;
	}
	return ;
}

void	ft_unset(t_shell *shell)
{
	char	**args;
	int		i;

	i = 1;
	args = shell->cmd->exec.args;
	while (args[i])
	{
		del_var_env(args[i], &shell->env);
		del_var_env(args[i], &shell->export);
		i++;
	}
	update_env(shell);
}
