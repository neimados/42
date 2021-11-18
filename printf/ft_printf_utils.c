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

