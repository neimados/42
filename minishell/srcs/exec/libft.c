/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:43:42 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/02 18:34:17 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	size_t	i;
	char	*str;

	i = 0;
	len = ft_strlen(src);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_loop(char *str, char const *s, unsigned int len, \
unsigned int start)
{
	unsigned int	i;

	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s))
	{
		str = ft_strdup("\0");
		return (str);
	}
	if (len < ft_strlen(s))
	{
		str = malloc(len + 1);
		if (!str)
			return (NULL);
	}
	else
	{
		str = malloc(ft_strlen(s) + 1);
		if (!str)
			return (NULL);
	}
	return (ft_loop(str, s, len, start));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	j = 0;
	lendest = ft_strlen(dest);
	i = lendest;
	lensrc = ft_strlen(src);
	if (size == 0 || size < i)
		return (size + lensrc);
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (lendest + lensrc);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			len;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcat((char *)str, (char *)s1, ft_strlen(s1) + 2);
	ft_strlcat((char *)str, (char *)s2, len + 2);
	return (str);
}
