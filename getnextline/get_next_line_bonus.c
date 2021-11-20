/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:29:33 by dso               #+#    #+#             */
/*   Updated: 2021/11/13 17:29:35 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *carry)
{
	int		i;
	char	*tmp;

	i = 1;
	if (carry != NULL && ft_strchr(carry, '\n') != NULL)
		return (carry);
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (ft_strchr(carry, '\n') == NULL && i != 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[i] = '\0';
		carry = ft_strjoin(carry, tmp);
	}
	free(tmp);
	return (carry);
}

char	*ft_findnl(char *carry)
{
	int		i;
	char	*str;

	i = 0;
	if (carry[i] == '\0')
		return (NULL);
	while (carry[i] && carry[i] != '\n')
		i++;
	if (carry[i] == '\n')
		str = ft_calloc((i + 2), sizeof(char));
	else
		str = ft_calloc((i + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (carry[i] && carry[i] != '\n')
	{
		str[i] = carry[i];
		i++;
	}
	if (carry[i] == '\n')
		str[i] = '\n';
	return (str);
}

char	*ft_carry(char *carry)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (carry[i] && carry[i] != '\n')
		i++;
	if (!carry[i])
	{
		free(carry);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(carry) - i + 1), sizeof(char));
	if (!next)
		return (NULL);
	i++;
	while (carry[i])
	{
		next[j] = carry[i];
		i++;
		j++;
	}
	free(carry);
	return (next);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*carry[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	carry[fd] = ft_read(fd, carry[fd]);
	if (!carry[fd])
		return (NULL);
	str = ft_findnl(carry[fd]);
	carry[fd] = ft_carry(carry[fd]);
	return (str);
}
