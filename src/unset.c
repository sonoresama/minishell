/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:22:22 by eorer             #+#    #+#             */
/*   Updated: 2023/05/24 15:23:09 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	lst_remove(t_env **lst)
{
	free((*lst)->str);
	free((*lst)->name);
	free((*lst)->value);
	free((*lst));
}

void	del_var(char *str, t_shell *shell)
{
	t_env	*lst;
	t_env	*tmp;

	tmp = NULL;
	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(str, lst->name, ft_strlen(lst->name)))
		{
			if (!tmp)
				shell->env = lst->next;
			else
				tmp->next = lst->next;
			lst_remove(&lst);
			return ;
		}
		tmp = lst;
		lst = lst->next;
	}
	return ;
}

int	ft_unset(t_shell *shell)
{
	char	**args;
	t_env	*lst;
	int	i;

	i = 1;
	args = shell->cmd->exec.args;
	lst = shell->env;
	while (args[i])
	{
		if (search_equal(args[i]))
		{
			write(2, "ERROR : Bad argument name", ft_strlen("ERROR : Bad argument name"));
			i++;
			continue ;
		}
		del_var(args[i], shell);
		i++;
	}
	if (update_env(shell))
		perror("MALLOC");
	return (FT_UNSET);
}
