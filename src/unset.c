/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:22:22 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 17:26:12 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	lst_remove(t_env **lst)
{
	t_env	**tmp;

	tmp = lst;
	free((*tmp)->str);
	free((*tmp)->name);
	free((*tmp)->value);
	*lst = (*tmp)->next;
	free(*tmp);
}

void	del_var(char *str, t_shell *shell)
{
	t_env	**lst;

	lst = &shell->env;
	while ((*lst)->next)
	{
		if (!ft_strncmp(str, (*lst)->str, ft_strlen(str)))
		{
			lst_remove(lst);
			return ;
		}
		else
			*lst = (*lst)->next;
	}
	return ;
}

int	ft_unset(t_shell *shell)
{
	char	**args;
	t_env	*lst;
	int	i;

	i = 0;
	args = shell->cmd->exec.args;
	lst = shell->env;
	while (args[i])
	{
		del_var(args[i], shell);
		i++;
	}
	return (FT_UNSET);

}
