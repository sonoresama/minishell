/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:20:52 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 11:21:08 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*dst;

	if (!dest && !src)
		return (dest);
	dst = dest;
	s = src;
	while (n)
	{
		*dst = *s;
		dst++;
		s++;
		n--;
	}
	return (dest);
}
