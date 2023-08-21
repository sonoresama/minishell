/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_with_last_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:45:25 by bastien           #+#    #+#             */
/*   Updated: 2023/08/21 12:45:42 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_join_with_last_error(char **str, int i, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	(*str)[i] = '\0';
	tmp = ft_itoa(shell->last_error);
	tmp2 = join_three((*str), tmp, &(*str)[i + 2]);
	free((*str));
	free(tmp);
	(*str) = tmp2;
}
