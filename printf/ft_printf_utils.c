/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:13:41 by dso               #+#    #+#             */
/*   Updated: 2021/11/15 18:13:43 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	c = (char)c;
	while (*str)
	{
		if (*str == c)
			return ((void *) str);
		str++;
	}
	if (c == '\0')
		return ((void *) str);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(size * count);
	i = 0;
	if (!ptr)
		return (NULL);
	while (i < size * count)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
