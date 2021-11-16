#include "ft_printf.h"


arglist	*ft_initlst(arglist *lst)
{
	lst->size;
	lst->zero;
	lst->plus;
	lst->minus;
	lst->dot;
	lst->space;
	lst->percent;
	return (lst);
}

int	ft_checkargs(const char *format, int i, arglist *lst)
{
	while (format[i] != 'c' || format[i] != 's' || format[i] != 'p'
	|| format[i] != 'd'|| format[i] != 'i'|| format[i] != 'u'
	|| format[i] != 's'|| format[i] != 'x' || format[i] != 'X'
	|| format[i] != '%')
	{
		if (format[i] == ' ')
			lst->space++;
		else if (format[i] == '0')
			lst->zero++;
		else if (format[i] == '+')
			lst->plus++;
		else if (format[i] == '-')
			lst->minus++;
		else if (format[i] == '.')
			lst->dot++;
		i++;
	}
	return (i - 1);
}

int	ft_printf(const char *format, ...)
{
	int	i;
	int	count;
	arglist *lst;

	i = 0;
	count = 0;
	lst = (arglist *)malloc(sizeof(arglist));
	if (!lst)
		return (-1);
	ft_initlst(lst);
	va_start(lst->args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			i = ft_checkargs(format, i, lst);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(lst->args);
}

int main()
{
	printf("% d", printf("%.1s%7d", "AAA", 123));
}