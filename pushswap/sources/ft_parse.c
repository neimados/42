/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:15 by dso               #+#    #+#             */
/*   Updated: 2021/12/02 00:02:12 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_parse(int argc, char **argv, t_stack *stack)
{
	int		i;
	int		j;
	int		minus;
	long	nb;

	i = 1;
	j = 0;
	minus = 0;
	nb = 0;
	if (argc == 2)
	{
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != 1 && argv[i][j] != ' ' && argv[i][j] != '-')
					return (1);
			else if (argv[i][j] == '-')
				minus = 1;
			else if (argv[i][j] == ' ')
			{
				if (minus == 1)
					nb = -nb;
				if (ft_checkargs(nb, stack) == 1)
					return (1);
				ft_push_bottom(stack, nb);
				nb = 0;
				minus = 0;
			}
			else
			{
				nb *= 10;
				nb += argv[i][j] - '0';
			}
			j++;
		}
		if (minus == 1)
			nb = -nb;
		if (ft_checkargs(nb, stack) == 1)
			return (1);
		ft_push_bottom(stack, nb);
	}
	else
	{
		while (i < argc)
		{
			while (argv[i][j])
			{
				if (ft_isdigit(argv[i][j]) != 1 && argv[i][j] != '-')
					return (1);
				if (argv[i][j] == '-')
				{
					j++;
					minus = 1;
				}
				nb *= 10;
				nb += argv[i][j] - '0';
				j++;
			}
			if (minus == 1)
				nb = -nb;
			if (ft_checkargs(nb, stack) == 1)
				return (1);
			ft_push_bottom(stack, nb);
			nb = 0;
			i++;
			j = 0;
			minus = 0;
		}
	}
	return (0);
}