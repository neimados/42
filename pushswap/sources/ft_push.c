/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:13:38 by dso               #+#    #+#             */
/*   Updated: 2021/12/01 10:38:05 by damien           ###   ########.fr       */
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
	write (1, "pb", 2);
}

void	ft_pa(t_stack *stacka, t_stack *stackb)
{
	t_node	*first;
	t_node *second;
	
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
	if(stacka->top == NULL)
	{
		stacka->top = first;
		stacka->bottom = first;
		stacka->top->prev = NULL;
	}
	else
	{
		second = stacka->top;
		second->next = first;
		stacka->top = first;
		stacka->top->prev = second;
	}
	write (1, "pa", 2);
}