/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mediumsort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:11:36 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:35:15 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_smalltop(t_stack *stacka, int *fromtop)
{
	t_node	*tmp;
	int		min;
	int		i;

	tmp = stacka->top;
	min = INT_MAX;
	i = 0;
	while (tmp)
	{
		if (tmp->value < min)
		{
			min = tmp->value;
			*fromtop = i;
		}
		tmp = tmp->prev;
		i++;
	}
	return (min);
}

void	ft_smallbottom(t_stack *stacka, int *frombottom)
{
	t_node	*tmp;
	int		min;
	int		i;

	tmp = stacka->bottom;
	min = INT_MAX;
	i = 0;
	while (tmp)
	{
		if (tmp->value < min)
		{
			min = tmp->value;
			*frombottom = i;
		}
		tmp = tmp->next;
		i++;
	}
}

void	ft_checkmedium(t_stack *stacka, t_stack *stackb)
{
	int		fromtop;
	int		frombottom;
	int		min;
	t_node	*tmp;

	tmp = stackb->top;
	fromtop = 0;
	frombottom = 0;
	while (ft_stacklen(stacka) != 0)
	{	
		min = ft_smalltop(stacka, &fromtop);
		ft_smallbottom(stacka, &frombottom);
		while (stacka->top->value != min)
		{
			if (fromtop <= frombottom)
				ft_ra(stacka);
			else
				ft_rra(stacka);
		}
		ft_pb(stacka, stackb);
	}
	while (ft_stacklen(stackb) != 0)
		ft_pa(stacka, stackb);
}
