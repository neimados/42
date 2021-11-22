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
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	va_list	args;
	int		space;
	int		zero;
	int		plus;
	int		minus;
	int		hash;
	int		dot;
	int		size;
	int		nb1;
	int		nb2;
}	t_arglist;

int		ft_printf(const char *s, ...);
void	ft_initlst(t_arglist *lst);
void	ft_putchar(t_arglist *lst, int *count);
void	ft_putstr(t_arglist *lst, int *count);
char	*ft_strchr(const char *str, int c);
int		ft_strlen(const char *str);
void	ft_putnbr(t_arglist *lst, int *count);
void	ft_putnbru(t_arglist *lst, int *count);
char	*ft_itoa(int n);
void	ft_putx(t_arglist *lst, int *count, char c);
char	*ft_putnbr_base(unsigned long nb, char *base);
void	ft_putp(t_arglist *lst, int *count);
char	*ft_putnbr_basep(unsigned long long nb, char *base);
void	*ft_calloc(size_t count, size_t size);

#endif
