/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:27:59 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:28:00 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(t_arglist *lst, int *count)
{
	int		i;
	char	b;

	i = 0;
	b = va_arg(lst->args, int);
	if (lst->minus >= 1)
		*count += write(1, &b, 1);
	while (i < lst->nb1 - 1)
	{
		*count += write(1, " ", 1);
		i++;
	}
	if (lst->minus == 0)
		*count += write(1, &b, 1);
}

static int	ft_checkstr(t_arglist *lst, int *count, char *str)
{
	if (lst->dot >= 1 && (lst->nb1 == 0 && lst->nb2 == 0))
		return (1);
	if (str == NULL)
	{
		*count += write(1, "(null)", 6);
		return (1);
	}
	return (0);
}

void	ft_putstr(t_arglist *lst, int *count)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	str = va_arg(lst->args, char *);
	if (ft_checkstr(lst, count, str) == 1)
		return ;
	if (lst->nb2 >= ft_strlen(str) || lst->nb2 == 0)
		size = ft_strlen(str);
	else
		size = lst->nb2;
	if (lst->minus >= 1)
		*count += write(1, str, size);
	while (i < lst->nb1 - size)
	{
		*count += write(1, " ", 1);
		i++;
	}
	if (lst->minus == 0)
		*count += write(1, str, size);
}
