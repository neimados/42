/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:55:26 by dso               #+#    #+#             */
/*   Updated: 2021/11/15 13:55:29 by dso              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct  s_list
{
    va_list    args;
    int        space;
    int        zero;
    int        plus;
    int        minus;
    int        hash;
    int        dot;
    int        size;
    int        nb1;
    int        nb2;
}    arglist;

int 	ft_printf(const char *, ...);
void    ft_putchar(arglist *lst, int *count);
void    ft_putstr(arglist *lst, int *count);
int 	ft_printargs(const char *s, int i, arglist *lst);
int    	ft_checkflags(const char *s, int i, arglist *lst);
char    *ft_strchr(const char *str, int c);
int 	ft_strlen(const char *str);
void	ft_percent(arglist *lst, int *count);
void	ft_putnbr(arglist *lst, int *count);
void	ft_putnbru(arglist *lst, int *count);
char	*ft_itoa(int n);
void	ft_putx(arglist *lst, int *count, char c);
char	*ft_putnbr_base(unsigned long nb, char *base);
void	ft_putp(arglist *lst, int *count);
char	*ft_putnbr_basep(unsigned long long nb, char *base);
void	*ft_calloc(size_t count, size_t size);

#endif
