/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:54:02 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 15:16:15 by dso              ###   ########.fr       */
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
	second = stacka->top;
	second->next = first;
	first->next = NULL;
	first->prev = second;
	stacka->top = first;
}

void	ft_rrb(t_stack *stackb)
{
	ft_rra(stackb);
}

void	ft_rrr(t_stack *stacka, t_stack *stackb)
{
	ft_rra(stacka);
	ft_rrb(stackb);
}