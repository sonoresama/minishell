/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:26:08 by eorer             #+#    #+#             */
/*   Updated: 2023/09/07 14:45:31 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_change_bis(t_shell *shell, char *old_pwd)
{
	t_env	*lst;

	lst = shell->env;
	if (!lst)
		return ;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "OLDPWD", 7))
		{
			free(lst->value);
			free(lst->str);
			lst->value = ft_strdup(old_pwd);
			lst->str = join_three("OLDPWD", "=", old_pwd);
			if (!lst->str)
				shell->error = MALLOC_ERROR;
			break ;
		}
		lst = lst->next;
	}
}

int	replace_var_cd(t_env **lst, char *old_pwd, char *pwd, t_shell *shell)
{
	ft_change_bis(shell, old_pwd);
	free((*lst)->str);
	free((*lst)->value);
	(*lst)->value = ft_strdup(pwd);
	(*lst)->str = join_three("PWD", "=", pwd);
	if (!(*lst)->str)
		shell->error = MALLOC_ERROR;
	return (0);
}
