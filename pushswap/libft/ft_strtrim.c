/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:01:33 by dso               #+#    #+#             */
/*   Updated: 2021/11/06 10:01:37 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checktrim(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = ft_strlen(s1) - 1;
	count = 1;
	while (ft_strchr(set, s1[i]) != NULL && s1[i])
		i++;
	while (ft_strrchr(set, s1[j]) != NULL && j > 0)
		j--;
	while (i <= j)
	{
		count++;
		i++;
	}
	return (count);
}

static char	*puttrim(char const *s1, char const *set, int size)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	while (ft_strchr(set, s1[i]) != NULL && s1[i])
		i++;
	while (ft_strrchr(set, s1[j]) != NULL && j > 0)
		j--;
	while (i <= j)
	{
		str[k] = s1[i];
		k++;
		i++;
	}
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*str;

	size = 0;
	if (!s1 || !set)
		return (NULL);
	size = checktrim(s1, set);
	str = puttrim(s1, set, size);
	return (str);
}
