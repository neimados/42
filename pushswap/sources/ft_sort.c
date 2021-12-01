/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:24:19 by dso               #+#    #+#             */
/*   Updated: 2021/12/01 23:48:20 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_checkthree(t_stack *stacka, int size)
{	
	if (stacka->top->value > stacka->top->prev->value
	&& stacka->top->value < stacka->bottom->value)
		ft_sa(stacka, size);
	else if (stacka->top->value > stacka->top->prev->value
	&& stacka->top->prev->value > stacka->bottom->value)
	{
		ft_sa(stacka, size);
		write(1, "\n", 1);
		ft_rra(stacka);
	}
	else if(stacka->bottom->value > stacka->bottom->next->value
	&& stacka->bottom->next->value < stacka->top->value)
		ft_ra(stacka);
	else if(stacka->bottom->value > stacka->top->value
	&& stacka->top->prev->value > stacka->bottom->value)
	{
		ft_sa(stacka, size);
		write(1, "\n", 1);
		ft_ra(stacka);
	}
	else
		ft_rra(stacka);
}

static void	ft_pushm(t_stack *stacka, t_stack *stackb, int nb)
{
	if (stacka->bottom->value == nb)
	{
		ft_rra(stacka);
		write(1, "\n", 1);
	}
	else
	{
		while (stacka->top->value != nb)
		{
			ft_ra(stacka);
			write(1, "\n", 1);
		}
	}
	ft_pb(stacka, stackb);
}

void	ft_checkfive(t_stack *stacka, t_stack *stackb, int size)
{
	int		max;
	int		min;
	
	max = ft_findbig(stacka);
	min = ft_findsmall(stacka);
	ft_pushm(stacka, stackb, min);
	write(1, "\n", 1);
	ft_pushm(stacka, stackb, max);
	write(1, "\n", 1);
	if (ft_checkorder(stacka) == 1)
	{
		ft_checkthree(stacka, size);
		write(1, "\n", 1);
	}
	ft_pa(stacka, stackb);
	write(1, "\n", 1);
	ft_ra(stacka);
	write(1, "\n", 1);
	ft_pa(stacka, stackb);
}