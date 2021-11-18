#include "ft_printf.h"

void	ft_putnbr(arglist *lst, int *count)
{
	int i;
	int nb;
	char *str;
	int size;

	i = 0;
	nb = va_arg(lst->args, int);
	if (lst->space >= 1 && (lst->minus == 0 && lst->plus == 0))
		*count += write(1, " ", 1);
	str = ft_itoa(nb);
	size = ft_strlen(str);
    if (lst->plus >= 1)
        i++;
    if (lst->minus >= 1)
    {   
        if (lst->plus >= 1 && nb > 0)
			*count += write(1, "+", 1);
        while (size + i < lst->nb2)
        {
            *count += write(1, "0", 1);
            i++;
        }
        *count += write(1, str, size);
    }
    if (lst->plus >= 1 && nb > 0 && lst->zero >= 1 && lst->minus == 0)
			*count += write(1, "+", 1);
    while (size + i < lst->nb1)
    {
		if (lst->zero >= 1 && (lst->minus == 0 || lst->plus == 0))
			*count += write(1, "0", 1);
		else
        	*count += write(1, " ", 1);
        i++;
    }
    if (lst->minus == 0)
    {
        if (lst->plus >= 1 && nb > 0 && lst->zero == 0)
			*count += write(1, "+", 1);
        while (size + i < lst->nb2)
        {
            *count += write(1, "0", 1);
            i++;
        }
        *count += write(1, str, size);
    }
}

void	ft_putnbru(arglist *lst, int *count)//NOT WORKING
{
    int i;
	int nb;
	char *str;
	int size;

	i = 1;
	nb = va_arg(lst->args, int);
    str = ft_itoa(nb);
	size = ft_strlen(str);
    if (lst->minus >= 1)
    {   
        while (size + i <= lst->nb2)
        {
        *count += write(1, "0", 1);
        i++;
        }
        *count += write(1, str, size);
    }
    while (*count < lst->nb1)
    {
		if (lst->zero >= 1 && (lst->minus == 0 || lst->plus == 0))
			*count += write(1, "0", 1);
		else
        	*count += write(1, " ", 1);
        i++;
    }
    if (lst->minus == 0)
    {
        while (size + i <= lst->nb2)
        {
        *count += write(1, "0", 1);
        i++;
        }
        *count += write(1, str, size);
    }
}
