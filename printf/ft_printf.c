/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:29:31 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:29:36 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_initnb(char c, int *nb)
{
	*nb *= 10;
	*nb += c - '0';
}

static int	ft_checkflags(const char *s, int i, t_arglist *lst)
{
	while (ft_strchr("cspdiuxX", s[i]) == NULL && s[i] != '%')
	{
		if (s[i] == '#')
			lst->hash++;
		else if (s[i] == ' ')
			lst->space++;
		else if (s[i] == '+')
			lst->plus++;
		else if (s[i] == '-')
			lst->minus++;
		else if (s[i] == '0' && (s[i - 1] > '9' || s[i - 1] < '0'))
			lst->zero++;
		else if (s[i] >= '0' && s[i] <= '9' && lst->dot == 0)
			ft_initnb(s[i], &lst->nb1);
		else if (s[i] == '.')
			lst->dot++;
		else if (s[i] >= '0' && s[i] <= '9' && lst->dot >= 1)
			ft_initnb(s[i], &lst->nb2);
		i++;
	}
	return (i);
}

static int	ft_printargs(const char *s, int i, t_arglist *lst)
{
	int	count;

	count = 0;
	if (s[i] == 'c')
		ft_putchar(lst, &count);
	else if (s[i] == 's')
		ft_putstr(lst, &count);
	else if (s[i] == '%')
		count += write(1, "%", 1);
	else if (s[i] == 'd' || s[i] == 'i')
		ft_putnbr(lst, &count);
	else if (s[i] == 'u')
		ft_putnbru(lst, &count);
	else if (s[i] == 'x' || s[i] == 'X')
		ft_putx(lst, &count, s[i]);
	else if (s[i] == 'p')
		ft_putp(lst, &count);
	return (count);
}

static void	ft_printfloop(const char *s, t_arglist *lst, int *count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			i = ft_checkflags(s, i, lst);
			*count += ft_printargs(s, i, lst);
			ft_initlst(lst);
		}
		else
			*count += write(1, &s[i], 1);
		i++;
	}
}

int	ft_printf(const char *s, ...)
{
	int			count;
	t_arglist	*lst;

	count = 0;
	lst = (t_arglist *)malloc(sizeof(t_arglist));
	if (!lst)
		return (-1);
	ft_initlst(lst);
	va_start(lst->args, s);
	ft_printfloop(s, lst, &count);
	va_end(lst->args);
	free(lst);
	return (count);
}
