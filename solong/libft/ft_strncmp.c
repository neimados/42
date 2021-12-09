/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:14:57 by dso               #+#    #+#             */
/*   Updated: 2021/11/04 10:18:46 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *a, const char *b, size_t size)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;
	int				diff;

	i = 0;
	diff = 0;
	s1 = (void *) a;
	s2 = (void *) b;
	while (i < size && diff == 0 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			diff = s1[i] - s2[i];
		i++;
	}
	return (diff);
}
