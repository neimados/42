/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:54:02 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:03:48 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_rra(t_stack *stacka)
{
	t_node	*first;
	t_node	*second;

	if (stacka->top->prev == NULL)
		return ;
	first = stacka->bottom;
	second = stacka->bottom->next;
	second->prev = NULL;
	stacka->bottom = second;
	first->prev = stacka->top;
	first->next = NULL;
	stacka->top->next = first;
	stacka->top = first;
	write(1, "rra\n", 4);
}

void	ft_rrb(t_stack *stackb)
{
	t_node	*first;
	t_node	*second;

	if (stackb->top->prev == NULL)
		return ;
	first = stackb->bottom;
	second = stackb->bottom->next;
	second->prev = NULL;
	stackb->bottom = second;
	first->prev = stackb->top;
	first->next = NULL;
	stackb->top->next = first;
	stackb->top = first;
	write(1, "rrb\n", 4);
}

void	ft_rrr(t_stack *stacka, t_stack *stackb)
{
	ft_rra(stacka);
	ft_rrb(stackb);
}
