/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:13:38 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 14:49:00 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_pb(t_stack *stacka, t_stack *stackb)
{
	t_node	*first;
	t_node *second;
	
	if (stacka->top == NULL)
		return ;
	first = stacka->top;
	if (first->prev != NULL)
	{
		second = stacka->top->prev;
		second->next = NULL;
		stacka->top = second;
	}
	else
	{
		stacka->top = NULL;
		stacka->bottom = NULL;
	}
	if(stackb->top == NULL)
	{
		stackb->top = first;
		stackb->bottom = first;
		stackb->top->prev = NULL;
	}
	else
	{
		second = stackb->top;
		second->next = first;
		stackb->top = first;
		stackb->top->prev = second;
	}
}

void	ft_pa(t_stack *stacka, t_stack *stackb)
{
	ft_pb(stackb, stacka);
}