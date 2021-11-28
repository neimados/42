/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:37:59 by dso               #+#    #+#             */
/*   Updated: 2021/11/04 11:47:51 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checks2(const char *s1, const char *s2, size_t i, size_t size)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		if (s1[i] == '\0' || s2[j] != s1[i])
			return (0);
		else if (i >= size)
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	if (s2[0] == '\0')
		return ((void *)s1);
	while (i < size && s1[i])
	{
		if (s1[i] == s2[0])
		{
			if (checks2(s1, s2, i, size) == 1)
				return ((void *)s1 + i);
		}
		i++;
	}
	return (NULL);
}
