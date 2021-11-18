#include "ft_printf.h"

static long	ft_counthex(long nb)
{
	long	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

char	*ft_putnbr_base(long nb, char *base)
{
	char	*str;
	int		i;

	i = ft_counthex(nb);
	str = malloc(sizeof(char) * (i + 1));
	str[i--] = '\0';
	while (nb)
	{
		str[i] = base[nb % 16];
		nb = nb / 16;
		i--;
	}
	return (str);
}