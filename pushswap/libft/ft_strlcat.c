/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:30:38 by dso               #+#    #+#             */
/*   Updated: 2021/11/04 11:16:19 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	destsize;
	size_t	srcsize;

	i = ft_strlen(dest);
	destsize = ft_strlen(dest);
	srcsize = ft_strlen(src);
	if (size == 0 || i > size)
		return (size + srcsize);
	while ((*src) && i < size - 1)
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return (destsize + srcsize);
}
