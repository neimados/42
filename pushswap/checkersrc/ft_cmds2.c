/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:21:25 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:37:30 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_pb2(t_stack *stacka, t_stack *stackb)
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
}

void	ft_pa2(t_stack *stacka, t_stack *stackb)
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
}

void	ft_rr2(t_stack *stacka, t_stack *stackb)
{
	ft_ra2(stacka);
	ft_rb2(stackb);
}

void	ft_rra2(t_stack *stacka)
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
}
