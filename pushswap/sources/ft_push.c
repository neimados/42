/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:13:38 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:28:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_p(t_stack *stack, t_node *first, t_node *second)
{
	if (stack->top == NULL)
	{
		stack->top = first;
		stack->bottom = first;
		stack->top->prev = NULL;
	}
	else
	{
		second = stack->top;
		second->next = first;
		stack->top = first;
		stack->top->prev = second;
	}
}

void	ft_pb(t_stack *stacka, t_stack *stackb)
{
	t_node	*first;
	t_node	*second;

	second = NULL;
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
	ft_p(stackb, first, second);
	write (1, "pb\n", 3);
}

void	ft_pa(t_stack *stacka, t_stack *stackb)
{
	t_node	*first;
	t_node	*second;

	second = NULL;
	if (stackb->top == NULL)
		return ;
	first = stackb->top;
	if (first->prev != NULL)
	{
		second = stackb->top->prev;
		second->next = NULL;
		stackb->top = second;
	}
	else
	{
		stackb->top = NULL;
		stackb->bottom = NULL;
	}
	ft_p(stacka, first, second);
	write (1, "pa\n", 3);
}
