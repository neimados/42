/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:09:00 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 14:11:23 by dso              ###   ########.fr       */
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
}

void	ft_rb(t_stack *stackb)
{
	ft_ra(stackb);
}

void	ft_rr(t_stack *stacka, t_stack *stackb)
{
	ft_ra(stacka);
	ft_rb(stackb);
}