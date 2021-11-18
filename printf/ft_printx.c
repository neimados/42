#include "ft_printf.h"


void	ft_putx(arglist *lst, int *count)
{
	int i;
	long nb;
	char *str;

	i = 0;
	nb = va_arg(lst->args, int);
	if (nb < 0)
		str = ft_putlong(nb);
	else
		str = ft_itoa(nb);
    if (lst->minus >= 1)
        ft_putleftx(lst, str, count);
    else
        ft_putrightx(lst, str, count);
	free(str);
}
