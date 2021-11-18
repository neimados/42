#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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

#endif