/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convbase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:34:03 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:34:04 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_counthex(unsigned long nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

char	*ft_putnbr_base(unsigned long nb, char *base)
{
	char	*str;
	int		i;

	if (nb < 0)
	{
		nb = -nb;
		nb = 4294967295 - nb + 1;
	}
	i = ft_counthex(nb);
	str = malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	while (nb)
	{
		str[i] = base[nb % 16];
		nb = nb / 16;
		i--;
	}
	return (str);
}

static int	ft_counthexp(unsigned long long nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

char	*ft_putnbr_basep(unsigned long long nb, char *base)
{
	char	*str;
	int		i;

	if (nb < 0)
	{
		nb = -nb;
		nb = 9223372036854775807 - nb + 1;
	}
	i = ft_counthexp(nb);
	str = malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	while (nb)
	{
		str[i] = base[nb % 16];
		nb = nb / 16;
		i--;
	}
	return (str);
}
