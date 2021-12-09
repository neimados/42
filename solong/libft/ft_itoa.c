/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:41:13 by dso               #+#    #+#             */
/*   Updated: 2021/11/06 16:41:15 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checklength(long n)
{
	int	i;

	i = 1;
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	fillstr(long nb, int size, char *str)
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
	int		minus;
	long	nb;

	minus = 0;
	nb = n;
	size = checklength(nb);
	if (nb < 0)
	{
		nb = -nb;
		minus++;
	}
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		*str = '0';
	fillstr(nb, size, str);
	if (minus != 0)
		str[0] = '-';
	return (str);
}
