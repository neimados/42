/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:52:47 by dso               #+#    #+#             */
/*   Updated: 2021/11/03 10:48:50 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	unsigned char	*b;
	unsigned char	c;
	size_t			i;

	i = 0;
	b = ptr;
	c = value;
	while (i < count)
	{
		b[i] = c;
		i++;
	}
	return (b);
}
