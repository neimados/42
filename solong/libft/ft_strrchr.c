/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:52:34 by dso               #+#    #+#             */
/*   Updated: 2021/11/03 15:11:10 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;

	i = 0;
	c = (char)c;
	while (str[i])
		i++;
	if (c == '\0')
		return ((void *) str + i);
	while (i)
	{
		if (str[i - 1] == c)
			return ((void *)str + i - 1);
		i--;
	}
	return (NULL);
}
