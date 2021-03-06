/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:09:00 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:04:01 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_ra(t_stack *stacka)
{
	t_node	*first;
	t_node	*second;

	if (stacka->top->prev == NULL)
		return ;
	first = stacka->top;
	second = stacka->top->prev;
	second->next = NULL;
	stacka->top = second;
	first->next = stacka->bottom;
	first->prev = NULL;
	stacka->bottom->prev = first;
	stacka->bottom = first;
	write(1, "ra\n", 3);
}

void	ft_rb(t_stack *stackb)
{
	t_node	*first;
	t_node	*second;

	if (stackb->top->prev == NULL)
		return ;
	first = stackb->top;
	second = stackb->top->prev;
	second->next = NULL;
	stackb->top = second;
	first->next = stackb->bottom;
	first->prev = NULL;
	stackb->bottom->prev = first;
	stackb->bottom = first;
	write(1, "rb\n", 3);
}

void	ft_rr(t_stack *stacka, t_stack *stackb)
{
	ft_ra(stacka);
	ft_rb(stackb);
}
