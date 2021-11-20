/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:29:31 by dso               #+#    #+#             */
/*   Updated: 2021/11/19 10:29:36 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    ft_initlst(arglist *lst)
{
    lst->space = 0;
    lst->zero = 0;
    lst->plus = 0;
    lst->minus = 0;
    lst->hash = 0;
    lst->dot = 0;
    lst->size = 0;
    lst->nb1 = 0;
    lst->nb2 = 0;
}

int    ft_checkflags(const char *s, int i, arglist *lst)
{
    while (ft_strchr("cspdiuxX", s[i]) == NULL && s[i] != '%')
    {
        if (s[i] == '#')
            lst->hash++;
        else if (s[i] == ' ')
            lst->space++;
        else if (s[i] == '+')
            lst->plus++;
        else if (s[i] == '-')
            lst->minus++;
        else if (s[i] == '0' && (s[i - 1] > '9' || s[i - 1] < '0'))
            lst->zero++;
        else if (s[i] >= '0' && s[i] <= '9' && lst->dot == 0)
        {
            lst->nb1 *= 10;
            lst->nb1 += s[i] - '0';
        }
        else if (s[i] == '.')
            lst->dot++;
        else if (s[i] >= '0' && s[i] <= '9' && lst->dot >= 1)
        {
            lst->nb2 *= 10;
            lst->nb2 += s[i] - '0';
        }
        i++;
    }
    return (i);
}

int ft_printargs(const char *s, int i, arglist *lst)
{
    int count;

    count = 0;
    if (s[i] == 'c')
        ft_putchar(lst, &count);
    else if (s[i] == 's')
        ft_putstr(lst, &count);
	else if (s[i] == '%')
		count += write(1, "%", 1);
	else if (s[i] == 'd' || s[i] == 'i')
        ft_putnbr(lst, &count);
    else if (s[i] == 'u')
        ft_putnbru(lst, &count);
    else if (s[i] == 'x' || s[i] == 'X')
        ft_putx(lst, &count, s[i]);
	else if (s[i] == 'p')
        ft_putp(lst, &count);
    return (count);
}

int    ft_printf(const char *s, ...)
{
    int    i;
    int count;
    arglist *lst;

    i = 0;
    count = 0;
    lst = (arglist *)malloc(sizeof(arglist));
    if (!lst)
        return (-1);
    ft_initlst(lst);
    va_start(lst->args, s);
    while (s[i])
    {
        if (s[i] == '%')
        {
            i++;
            i = ft_checkflags(s, i, lst);
            count += ft_printargs(s, i, lst);
            ft_initlst(lst);
        }
        else
            count += write(1, &s[i], 1);
        i++;
    }
    va_end(lst->args);
    free(lst);
    return (count);
}

// int main()
// {
// 	//printf("%i", printf("%-.8d ", -1));
// 	//printf("\n");
// 	//printf("%i", ft_printf("%-.8d ", -1));

//     //printf("%d", printf("%.s ", "-"));
// 	//printf("\n");
// 	//printf("%d", ft_printf("%.s ", "-"));
    
//     //printf("%d", printf("%.12d ", -1));
//     //printf("\n");
//     //printf("%d", ft_printf("%.12d ", -1));

//     //printf("%d", printf(" %u ", -1));
//     //printf("\n");
//     //printf("%d", ft_printf(" %u ", -1));

//     //printf("%d", printf("%-13x ", UINT_MAX));
//     //printf("\n");
//     //printf("%d", ft_printf("%-13x ", UINT_MAX));

// 	printf("%d", printf("%#x ", 0));
//     printf("\n");
//     printf("%d", ft_printf("%#x ", 0));

// 	//char *str = "test";
// 	//int tab[] = {0, 0};
// 	//printf("%d", printf("%p ", (void *)0));
//     //printf("\n");
//     //printf("%d", ft_printf("%p ", (void *)0));
// }
