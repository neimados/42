/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:13:37 by dso               #+#    #+#             */
/*   Updated: 2021/11/03 16:13:41 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char		*b;
	const char	*c;

	if (!dest && !src)
		return (NULL);
	b = dest;
	c = src;
	if (b < c)
	{
		while (size)
		{
			*b++ = *c++;
			size--;
		}
	}
	else
	{
		while (size)
		{
			b[size - 1] = c[size - 1];
			size--;
		}
	}
	return (dest);
}
