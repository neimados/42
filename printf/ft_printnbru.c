/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbru.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:31:28 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:31:30 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putleftu(t_arglist *lst, char *str, int *count)
{
	int	i;
	int	max;

	i = ft_strlen(str);
	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	while (i < lst->nb2)
	{
		*count += write(1, "0", 1);
		i++;
	}
	*count += write(1, str, ft_strlen(str));
	while (*count < max)
	{
		*count += write(1, " ", 1);
		i++;
	}
}

static int	ft_checkuright(t_arglist *lst, int *count, int size)
{
	int	max;

	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	if (lst->nb2 > size)
		*count += lst->nb2;
	else
		*count += size;
	return (max);
}

static void	ft_putrightu(t_arglist *lst, char *str, int *count)
{
	int	i;
	int	size;
	int	max;

	size = ft_strlen(str);
	i = size;
	max = ft_checkuright(lst, count, size);
	while (*count < max)
	{
		if (lst->zero >= 1)
			*count += write(1, "0", 1);
		else
			*count += write(1, " ", 1);
	}
	while (i < lst->nb2)
	{
		write(1, "0", 1);
		i++;
	}
	write(1, str, size);
}

static char	*ft_putlong(long nb)
{
	int				i;
	char			*str;
	unsigned long	tmp;

	i = 0;
	nb = -nb;
	tmp = 4294967295 - nb + 1;
	while (tmp != 0)
	{
		tmp /= 10;
		i++;
	}
	tmp = 4294967295 - nb + 1;
	str = malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = (tmp % 10) + '0';
		tmp /= 10;
		i--;
	}
	return (str);
}

void	ft_putnbru(t_arglist *lst, int *count)
{
	int		i;
	long	nb;
	char	*str;

	i = 0;
	nb = va_arg(lst->args, int);
	if (nb < 0)
		str = ft_putlong(nb);
	else
		str = ft_itoa(nb);
	if (lst->minus >= 1)
		ft_putleftu(lst, str, count);
	else
		ft_putrightu(lst, str, count);
	free(str);
}
