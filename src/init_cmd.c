/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:21:01 by blerouss          #+#    #+#             */
/*   Updated: 2023/05/17 17:06:05 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_cmd(t_cmd **cmd, t_cmd **start, char **env)
{
	(*cmd) = malloc(sizeof(t_cmd));
	if ((*cmd) == NULL)
	{
		perror("Allocation error : ");
		exit(1);
	}
	if (start)
		(*start) = (*cmd);
	ft_bzero((*cmd), sizeof(t_cmd));
	(*cmd)->env = ft_parse_env(env);	
}

void	ft_init_cmd_2(t_cmd **cmd, t_cmd **start, t_env *env)
{
	(*cmd) = malloc(sizeof(t_cmd));
	if ((*cmd) == NULL)
	{
		perror("Allocation error : ");
		exit(1);
	}
	if (start)
		(*start) = (*cmd);
	ft_bzero((*cmd), sizeof(t_cmd));
	(*cmd)->env = env;	
}
