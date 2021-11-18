#include "ft_printf.h"

static void    ft_putleft(arglist *lst, long nb, char *str, int *count)
{
    int i;
	int max;

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

static void    ft_putright(arglist *lst, long nb, char *str, int *count)
{
	int i;
	int max;

	i = ft_strlen(str);
	max = 0;
	if (lst->nb2 > lst->nb1)
		max += lst->nb2;
	else
		max += lst->nb1;
	if (lst->nb2 > ft_strlen(str))
		*count += lst->nb2;
	else
		*count += ft_strlen(str);
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
	write(1, str, ft_strlen(str));
}

void	ft_putnbru(arglist *lst, int *count)
{
	int i;
	long nb;
	char *str;

	i = 0;
	nb = va_arg(lst->args, int);
	str = ft_itoa(nb);
    if (lst->minus >= 1)
        ft_putleft(lst, nb, str, count);
    else
        ft_putright(lst, nb, str, count);
}


