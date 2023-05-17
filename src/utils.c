/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:08:50 by eorer             #+#    #+#             */
/*   Updated: 2023/05/17 17:09:54 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return(i);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;
	while (env)
	{
		if (env->str)
			free(env->str);
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	ft_clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd && cmd->env)
		ft_free_env(cmd->env);
	while (cmd)
	{
		if (cmd->args)
		{
			ft_print_tab(cmd->args);
			ft_free_tab(cmd->args);
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
