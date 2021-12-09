/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:25:49 by dso               #+#    #+#             */
/*   Updated: 2021/11/04 10:25:17 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int c, size_t size)
{
	unsigned char	*b;
	unsigned char	ch;
	size_t			i;

	b = (void *) mem;
	ch = c;
	i = 0;
	while (i < size)
	{
		if (b[i] == ch)
			return ((char *)b + i);
		i++;
	}
	return (NULL);
}
