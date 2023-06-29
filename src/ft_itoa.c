/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:48:14 by blerouss          #+#    #+#             */
/*   Updated: 2022/11/15 17:05:57 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_fill_string(long int n, char *res, size_t i)
{
	if (n < 0)
	{
		n = n * -1;
		res[0] = '-';
	}
	while (n > 9)
	{
		res[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	res[i] = n % 10 + '0';
	return (res);
}

char	*ft_itoa(int n)
{
	size_t	i;
	long	tmp;
	char	*res;

	tmp = n;
	i = 1;
	while (tmp > 9 || tmp < -9)
	{
		tmp = tmp / 10;
		i++;
	}
	if (n < 0)
		i++;
	res = (char *)malloc(i + 1);
	if (res == NULL)
		return (NULL);
	res = ft_fill_string((long int)n, res, i - 1);
	res[i] = '\0';
	return (res);
}
/*
int	main()
{
	int	i;
	char	*str;

	i = 0;
	str = ft_itoa(i);
	printf("%s\n", str);
	free(str);
}*/
