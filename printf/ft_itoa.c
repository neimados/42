/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:26:54 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:26:56 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	checklength(long n)
{
	int	i;

	i = 1;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	fillstr(long nb, int size, char *str)
{
	while (nb != 0)
	{
		str[size - 2] = (nb % 10) + '0';
		size--;
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	nb;

	nb = n;
	if (nb < 0)
		nb = -nb;
	size = checklength(nb);
	str = ft_calloc(size, sizeof(char) + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		*str = '0';
	fillstr(nb, size, str);
	return (str);
}
