/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:10:42 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:36:30 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_stack *stacka, int size)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;

	if (stacka == NULL || stacka->top->prev == NULL)
		return ;
	first = stacka->top;
	second = first->prev;
	if (size >= 3)
	{
		third = second->prev;
		third->next = first;
		first->prev = third;
	}
	else
	{
		first->prev = NULL;
		stacka->bottom = first;
	}
	first->next = second;
	second->next = NULL;
	second->prev = first;
	stacka->top = second;
	write(1, "sa\n", 3);
}

void	ft_sb(t_stack *stackb, int size)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;

	if (stackb == NULL || stackb->top->prev == NULL)
		return ;
	first = stackb->top;
	second = first->prev;
	if (size >= 3)
	{
		third = second->prev;
		third->next = first;
		first->prev = third;
	}
	else
	{
		first->prev = NULL;
		stackb->bottom = first;
	}
	first->next = second;
	second->next = NULL;
	second->prev = first;
	stackb->top = second;
	write(1, "sb\n", 3);
}

void	ft_ss(t_stack *stacka, t_stack *stackb, int size)
{
	ft_sa(stacka, size);
	ft_sb(stackb, size);
}
