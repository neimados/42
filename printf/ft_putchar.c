#include "ft_printf.h"

void    ft_putchar(arglist *lst, int *count)
{
    int    i;
    char    b;

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

void    ft_putstr(arglist *lst, int *count)
{
    int    i;
	int size;
    char    *str;

    i = 0;
	str = va_arg(lst->args, char *);
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