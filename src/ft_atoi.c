/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:50:46 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 16:17:29 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

t_long	ft_atoi(const char *nptr)
{
	t_long	neg;
	t_long	resultat;

	resultat = 0;
	neg = 1;
	while ((*nptr >= 8 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		neg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr) && *nptr)
	{
		resultat = resultat * 10 + *nptr - '0';
		nptr++;
	}
	if (*nptr)
		return (0);
	return (resultat * neg);
}
