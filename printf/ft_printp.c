/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:05:03 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 11:05:07 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putleftp(t_arglist *lst, char *str, int *count, int size)
{
	int	i;
	int	max;

	i = size;
	max = lst->nb1;
	*count += write(1, "0x", 2);
	*count += write(1, str, size);
	while (*count < max)
	{
		*count += write(1, " ", 1);
		i++;
	}
}

static void	ft_putrightp(t_arglist *lst, char *str, int *count, int size)
{
	int	i;
	int	max;

	i = size;
	max = lst->nb1;
	*count += size + 2;
	while (*count < max)
		*count += write(1, " ", 1);
	write(1, "0x", 2);
	write(1, str, size);
}

void	ft_putp(t_arglist *lst, int *count)
{
	unsigned long long	addr;
	char				*str;
	int					size;

	addr = va_arg(lst->args, unsigned long);
	if (addr == 0)
	{
		*count += write(1, "0x0", 3);
		return ;
	}
	str = ft_putnbr_basep(addr, "0123456789abcdef");
	size = ft_strlen(str);
	if (lst->minus >= 1)
		ft_putleftp(lst, str, count, size);
	else
		ft_putrightp(lst, str, count, size);
	free(str);
}
