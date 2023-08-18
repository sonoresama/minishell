/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:29:34 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 12:03:49 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	if (env->str)
		free(env->str);
	free(env);
}
