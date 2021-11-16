#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>

typedef struct slist
{
	va_list args;
	int size;
	int zero;
	int plus;
	int minus;
	int dot;
	int space;
	int percent;
}	arglist;

int ft_printf(const char *, ...);

#endif