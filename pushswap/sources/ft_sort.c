/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:24:19 by dso               #+#    #+#             */
/*   Updated: 2021/12/01 00:15:30 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_checkorder(t_stack *stacka)
{
	t_node	*tmp;

	tmp = stacka->top;
	while (tmp->prev != NULL)
	{
		if (tmp->value > tmp->prev->value)
			return (1);
		tmp = tmp->prev;
	}
	return (0);
}

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