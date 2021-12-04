/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:15 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:16:37 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

static int	ft_onearg(char **argv, t_stack *stack, int j)
{
	long	nb;
	int		minus;

	nb = 0;
	minus = 0;
	while (argv[1][j])
	{
		if (ft_checkone(argv[1][j]) == 1)
			return (1);
		else if (argv[1][j] == '-')
			minus += 1;
		else if (argv[1][j] == ' ')
		{
			if (ft_onearg2(stack, &nb, &minus) == 1)
				return (1);
		}
		else
			ft_nbr(&nb, argv[1][j]);
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
	int	j;

	j = 0;
	if (argc == 2)
	{
		if (ft_onearg(argv, stack, j) == 1)
			return (1);
	}
	else
	{
		if (ft_args(argc, argv, stack) == 1)
			return (1);
	}
	return (0);
}
