/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:15 by dso               #+#    #+#             */
/*   Updated: 2021/12/02 10:51:39 by damien           ###   ########.fr       */
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
				minus++;
			else if (argv[i][j] == ' ')
			{
				if (minus == 1)
					nb = -nb;
				else if (minus > 1)
					return (1);
				if (ft_checkargs(nb, stack) == 1)
					return (1);
				if (!ft_push_bottom(stack, nb))
				{
					free(stack);
					return(1);
				}
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
		else if (minus > 1)
			return (1);
		if (ft_checkargs(nb, stack) == 1)
			return (1);
		if (!ft_push_bottom(stack, nb))
		{
			free(stack);
			return(1);
		}
	}
	else
	{
		while (i < argc)
		{
			while (argv[i][j])
			{
				if (ft_isdigit(argv[i][j]) != 1 && argv[i][j] != '-')
					return (1);
				while (argv[i][j] == '-')
				{
					j++;
					minus++;
				}
				nb *= 10;
				nb += argv[i][j] - '0';
				j++;
			}
			if (minus == 1)
				nb = -nb;
			else if (minus > 1)
				return (1);
			if (ft_checkargs(nb, stack) == 1)
				return (1);
			if (!ft_push_bottom(stack, nb))
			{
				free(stack);
				return(1);
			}
			nb = 0;
			i++;
			j = 0;
			minus = 0;
		}
	}
	return (0);
}