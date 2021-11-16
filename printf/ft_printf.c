#include "ft_printf.h"


arglist	*ft_initlst(arglist *lst)
{
	lst->size = 0;
	lst->zero = 0;
	lst->plus = 0;
	lst->minus = 0;
	lst->dot = 0;
	lst->space = 0;
	lst->percent = 0;
	return (lst);
}

int	ft_checkflags(const char *format, int i, arglist *lst)
{
	int count;

	count = 0;
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
		{	
			lst->plus++;
			count++;
		}
		else if (format[i] == '-')
		{
			lst->minus++;
			count++;
		}
		else if (format[i] == '.')
		{
			lst->dot++;
			count++;
		}
		i++;
	}
	if (count != 1)
		return (-1);
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
			i = ft_checkflags(format, i, lst);
			if (i == -1)
				return (-1);
			count += ft_checkargs(format[i], lst);
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