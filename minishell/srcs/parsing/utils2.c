/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:01:29 by dso               #+#    #+#             */
/*   Updated: 2022/02/12 16:42:57 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > d_strlen(s))
		len = d_strlen(s);
	str = d_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (d_strlen(s) < start)
	{
		*str = '\0';
		return (str);
	}
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	d_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	d_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		d_putchar_fd(*s, fd);
		s++;
	}
}

char	*d_strchr(const char *str, int c)
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

int	d_atoi(const char *str)
{
	long	res;
	long	minus;

	res = 0;
	minus = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
		if (res > 2147483648 && minus == -1)
			return (0);
		else if (res > 2147483647 && minus == 1)
			return (-1);
	}
	return (res * minus);
}
