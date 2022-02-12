/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:52:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/12 16:11:51 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_strchr2(const char *str, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return ((void *) &str[i]);
		i++;
	}
	if (c == '\0')
		return ((void *) &str[i]);
	return (NULL);
}

char	*d_strjoin2(char *s1, char *s2)
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
	str = d_calloc((ft_strlen(s1) + d_strlen(s2) + 1), sizeof(char));
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
