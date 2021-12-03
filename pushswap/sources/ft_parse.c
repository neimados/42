/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:15 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 14:15:27 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_onearg2(char c, t_stack *stack, long *nb, int *minus)
{
	if (ft_isdigit(c) != 1 && c != ' ' && c != '-')
		return (1);
	else if (c == '-')
		*minus += 1;
	else if (c == ' ')
	{
		if (*minus == 1)
			*nb = -*nb;
		if (ft_checkfail(*minus, stack, *nb) == 1)
			return (1);
		*nb = 0;
		*minus = 0;
	}
	return (0);
}

static int	ft_onearg(char **argv, t_stack *stack)
{
	int		j;
	long	nb;
	int		minus;

	j = 0;
	nb = 0;
	minus = 0;
	while (argv[1][j])
	{
		if (ft_onearg2(argv[1][j], stack, &nb, &minus) == 1)
			return (1);
		else
		{
			nb *= 10;
			nb += argv[1][j] - '0';
		}
		j++;
	}
	if (minus == 1)
		nb = -nb;
	if (ft_checkfail(minus, stack, nb) == 1)
		return (1);
	return (0);
}

static int	ft_args2(char **argv, long *nb, int *minus, int i)
{
	int	j;

	j = 0;
	while (argv[i][j])
	{
		if (ft_isdigit(argv[i][j]) != 1 && argv[i][j] != '-')
			return (1);
		while (argv[i][j] == '-')
		{
			j++;
			*minus += 1;
		}
		*nb *= 10;
		*nb += argv[i][j] - '0';
		j++;
	}
	return (0);
}

static int	ft_args(int argc, char **argv, t_stack *stack)
{
	int		i;
	int		j;
	long	nb;
	int		minus;

	i = 1;
	j = 0;
	nb = 0;
	minus = 0;
	while (i < argc)
	{
		if (ft_args2(argv, &nb, &minus, i) == 1)
			return (1);
		if (minus == 1)
			nb = -nb;
		if (ft_checkfail(minus, stack, nb) == 1)
			return (1);
		nb = 0;
		i++;
		j = 0;
		minus = 0;
	}
	return (0);
}

int	ft_parse(int argc, char **argv, t_stack *stack)
{
	if (argc == 2)
	{
		if (ft_onearg(argv, stack) == 1)
			return (1);
	}
	else
	{
		if (ft_args(argc, argv, stack) == 1)
			return (1);
	}
	return (0);
}
