#include "ft_printf.h"

char    *ft_strchr(const char *str, int c)
{
    int    i;

    i = 0;
    c = (char)c;
    if (!str)
        return (NULL);
    while (str[i])
    {
        if (str[i] == c)
            return ((void *) &str[i]);
        i++;
    }
    if (c == '\0')
        return ((void *) &str[i]);
    return (NULL);
}

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_itoa(int n)
{
	int				col;
	int				on;
	char			*str;
	unsigned int	temp;

	on = n < 0 ? 1 : 0;
	col = n;
	temp = (n < 0) ? (-n) : n;
	while (n > 8 || n < -8)
	{
		on++;
		n = n / 10;
	}
	if (!(str = (char *)malloc(sizeof(char) * (on + 2))))
		return (NULL);
	str[on + 1] = '\0';
	while (on > -1)
	{
		str[on--] = (temp % 10) + '0';
		temp = temp / 10;
	}
	str[0] = col < 0 ? '-' : str[0];
	return (str);
}