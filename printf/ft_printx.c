#include "ft_printf.h"

static void	ft_putxleft(arglist *lst, char *str, long size, int *count)
{
    int i;
	int max;

	i = size;
	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	if (lst->hash >= 1)
		*count += write(1, "0x", 2);
	while (i < lst->nb2)
	{
		*count += write(1, "0", 1);
		i++;
	}
	*count += write(1, str, size);
	while (*count < max)
	{
		*count += write(1, " ", 1);
		i++;
	}
}

static void	ft_putxright(arglist *lst, char *str, long size, int *count)
{
	int i;
	int max;

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
		write(1, "0x", 2);
	while (*count < max)
	{
		if (lst->zero >= 1)
			*count += write(1, "0", 1);
		else
			*count += write(1, " ", 1);
	}
	if (lst->hash >= 1 && lst->zero == 0)
		write(1, "0x", 2);
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
	long nb;
	char *str;

	nb = va_arg(lst->args, int);
	if (nb == 0)
	{
		*count += write(1, "0", 1);
		return ;
	}
	if (c == 'x')
		str = ft_putnbr_base(nb, "0123456789abcdef");
	else
		str = ft_putnbr_base(nb, "0123456789ABCDEF");
	size = ft_strlen(str);
	if (lst->minus >= 1)
		ft_putxleft(lst, str, size, count);
	else
		ft_putxright(lst, str, size, count);
	free(str);
}

