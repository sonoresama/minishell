/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:30:12 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 17:01:37 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_export(char *str)
{
	if (str[0] == '=')
	{
		write(2, "ERROR : arg not found\n", 22);
		return (1);
	}
	else if (!search_equal(str))
		return (1);
	return(0);
}

int	check_doublon(char *str, t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(str, lst->name, ft_strlen(str)))
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_env	*check_all(char *str, t_shell *shell)
{
	t_env	*new;

	if (check_export(str))
		return (NULL);
	new = ft_create_var_env(str);
	if (!new)
	{
		write(2, "ERROR : malloc exploded", 23);
		return (NULL);
	}
	if (check_doublon(new->name, shell))
	{
		//free_maillon();
		return (NULL);
	}
	return (new);
}

int	ft_export(t_shell *shell)
{
	char	**args;
	t_env	*new;
	int	i;

	args = shell->cmd->exec.args;
	i = 1;
	if (!args[i])
	{
		ft_env(shell);
		return (FT_EXPORT);
	}
	while (args[i])
	{
		new = check_all(args[i], shell);
		if (!new)
			return (FT_EXPORT);
		else
			lst_add_end(&shell->env, new);
		i++;
	}
	return (FT_EXPORT);
}
