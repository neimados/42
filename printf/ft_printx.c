/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:32:06 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:32:08 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putxleft(arglist *lst, char *str, int *count, char c)
{
    int i;
	int max;

	i = ft_strlen(str);
	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	if (lst->hash >= 1)
	{
		*count += write(1, "0", 1);
		*count += write(1, &c, 1);
	}
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

static void	ft_putxright(arglist *lst, char *str, int *count, char c)
{
	int i;
	int size;
	int max;

	size = ft_strlen(str);
	i = size;
	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	if (lst->nb2 > size)
		*count += lst->nb2;
	else
		*count += size;
	if (lst->hash >= 1)
		*count += 2;
	if (lst->hash >= 1 && lst->zero >= 1)
	{
		write(1, "0", 1);
		write(1, &c, 1);
	}
	while (*count < max)
	{
		if (lst->zero >= 1)
			*count += write(1, "0", 1);
		else
			*count += write(1, " ", 1);
	}
	if (lst->hash >= 1 && lst->zero == 0)
	{
		write(1, "0", 1);
		write(1, &c, 1);
	}
	while (i < lst->nb2)
	{
		write(1, "0", 1);
		i++;
	}
	write(1, str, ft_strlen(str));
}

void	ft_putx(arglist *lst, int *count, char c)
{
	long size;
	unsigned long nb;
	char *str;

	nb = va_arg(lst->args, unsigned int);
	if (nb == 0 && lst->hash >= 1)
	{
		*count += write(1, "0", 1);
		return ;
	}
	else if (nb == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
	}
	else
	{
		if (c == 'x')
			str = ft_putnbr_base(nb, "0123456789abcdef");
		else
			str = ft_putnbr_base(nb, "0123456789ABCDEF");
	}
	size = ft_strlen(str);
	if (lst->minus >= 1)
		ft_putxleft(lst, str, count, c);
	else
		ft_putxright(lst, str, count, c);
	free(str);
}
