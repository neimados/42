/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:30:53 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:30:55 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putleft(t_arglist *lst, long nb, char *str, int *count)
{
	int	i;
	int	max;

	i = ft_strlen(str);
	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	if (lst->plus >= 1 && nb >= 0)
		*count += write(1, "+", 1);
	else if (lst->plus == 0 && lst->space >= 1 && nb >= 0)
		*count += write(1, " ", 1);
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

static int	ft_checkright(t_arglist *lst, int *count, int size, long nb)
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
	if (lst->plus >= 1 && nb >= 0)
		*count += 1;
	else if (lst->plus == 0 && lst->space >= 1 && nb >= 0)
		*count += write(1, " ", 1);
	if (lst->plus >= 1 && lst->zero >= 1 && nb >= 0)
		write(1, "+", 1);
	return (max);
}

static void	ft_putright(t_arglist *lst, long nb, char *str, int *count)
{
	int	i;
	int	size;
	int	max;

	size = ft_strlen(str);
	i = size;
	max = ft_checkright(lst, count, size, nb);
	while (*count < max)
	{
		if (lst->zero >= 1)
			*count += write(1, "0", 1);
		else
			*count += write(1, " ", 1);
	}
	if (lst->plus >= 1 && lst->zero == 0 && nb >= 0)
		write(1, "+", 1);
	while (i < lst->nb2)
	{
		write(1, "0", 1);
		i++;
	}
	write(1, str, ft_strlen(str));
}

void	ft_putnbr(t_arglist *lst, int *count)
{
	int		i;
	long	nb;
	char	*str;

	i = 0;
	nb = va_arg(lst->args, int);
	if (nb < 0)
		*count += write(1, "-", 1);
	str = ft_itoa(nb);
	if (lst->minus >= 1)
		ft_putleft(lst, nb, str, count);
	else
		ft_putright(lst, nb, str, count);
	free(str);
}
