/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emileorer <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:50:34 by emileorer         #+#    #+#             */
/*   Updated: 2023/07/03 15:51:03 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_alpha(char a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return (1);
	return (0);
}

int	is_digit(char a)
{
	if (a >= 48 && a <= 57)
		return (1);
	return (0);
}

int	is_all_alpha_num(char *str)
{
	int	i;

	i = 0;
	if (!str || !is_alpha(str[i]))
		return (0);
	while (str[i] && (is_alpha(str[i]) || is_digit(str[i])) && str[i] != '=')
		i++;
	if (!is_alpha(str[i]) && !is_digit(str[i]) && str[i] != '=' && str[i])
		return (0);
	return (1);
}

int	check_export(char *str, t_shell *shell)
{
	if (!is_all_alpha_num(str))
	{
		shell->last_error = 1;
		write(2, "ERROR : no valid operator\n", 27);
		return (1);
	}
	if (str[0] == '=')
	{
		shell->last_error = 1;
		write(2, "ERROR : arg not found\n", 23);
		return (1);
	}
	return(0);
}
