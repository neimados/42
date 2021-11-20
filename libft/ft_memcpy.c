/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:47:52 by dso               #+#    #+#             */
/*   Updated: 2021/11/03 10:51:04 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char		*b;
	const unsigned char	*c;
	size_t				i;

	if (!dest && !src && size != 0)
		return (NULL);
	i = 0;
	b = dest;
	c = src;
	while (i < size)
	{
		b[i] = c[i];
		i++;
	}
	return (b);
}
