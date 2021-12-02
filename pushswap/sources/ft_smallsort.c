/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:24:19 by dso               #+#    #+#             */
/*   Updated: 2021/12/02 12:59:01 by damien           ###   ########.fr       */
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
		ft_rra(stacka);
	}
	else if(stacka->bottom->value > stacka->bottom->next->value
	&& stacka->bottom->next->value < stacka->top->value)
		ft_ra(stacka);
	else if(stacka->bottom->value > stacka->top->value
	&& stacka->top->prev->value > stacka->bottom->value)
	{
		ft_sa(stacka, size);
		ft_ra(stacka);
	}
	else
		ft_rra(stacka);
}

static void	ft_pushm(t_stack *stacka, t_stack *stackb, int nb)
{
	if (stacka->bottom->value == nb)
		ft_rra(stacka);
	else
	{
		while (stacka->top->value != nb)
			ft_ra(stacka);
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
	ft_pushm(stacka, stackb, max);
	if (ft_checkorder(stacka) == 1)
		ft_checkthree(stacka, size);
	ft_pa(stacka, stackb);
	ft_ra(stacka);
	ft_pa(stacka, stackb);
}