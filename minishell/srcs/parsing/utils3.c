/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:37:45 by dso               #+#    #+#             */
/*   Updated: 2022/02/09 16:05:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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