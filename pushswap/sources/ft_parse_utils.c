/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:14:40 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:17:44 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_checkfail(int minus, t_stack *stack, long nb)
{
	if (minus > 1)
		return (1);
	if (ft_checkargs(nb, stack) == 1)
		return (1);
	if (!ft_push_bottom(stack, nb))
	{
		ft_free(stack);
		return (1);
	}
	return (0);
}

int	ft_onearg2(t_stack *stack, long *nb, int *minus)
{
	if (*minus == 1)
		*nb = -*nb;
	if (ft_checkfail(*minus, stack, *nb) == 1)
		return (1);
	*nb = 0;
	*minus = 0;
	return (0);
}

void	ft_nbr(long *nb, char c)
{
	*nb *= 10;
	*nb += c - '0';
}

int	ft_checkone(char c)
{
	if (ft_isdigit(c) != 1 && c != ' ' && c != '-')
		return (1);
	else
		return (0);
}
