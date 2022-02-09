/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:33:04 by dso               #+#    #+#             */
/*   Updated: 2022/02/07 12:01:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_strdup(const char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
		i++;
	dup = malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	d_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*d_calloc(size_t count, size_t size)
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

char	*d_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		s1 = d_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = d_calloc((d_strlen(s1) + d_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	return (str);
}

int	d_strncmp(const char *a, const char *b, size_t size)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;
	int				diff;

	i = 0;
	diff = 0;
	if (d_strlen(a) != d_strlen(b))
		return (-1);
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
