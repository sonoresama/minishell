/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env_in_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:30:35 by bastien           #+#    #+#             */
/*   Updated: 2023/08/29 16:45:16 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	replace_var_env_in_lst(t_parsing *parsing, t_shell *shell)
{
	t_quote	*tmp;

	tmp = NULL;
	if (parsing && parsing->dquote)
		tmp = parsing->dquote;
	while (tmp)
	{
		replace_var_env_in_str(&tmp->str, shell);
		if (shell->error == MALLOC_ERROR)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
