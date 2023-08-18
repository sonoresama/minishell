/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env_in_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:30:35 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 18:30:52 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_var_env_in_lst(t_parsing *parsing, t_shell *shell)
{
	t_quote	*tmp;

	tmp = NULL;
	if (parsing && parsing->dquote)
		tmp = parsing->dquote;
	while (tmp)
	{
		replace_var_env_in_str(&tmp->str, shell);
		tmp = tmp->next;
	}
}
