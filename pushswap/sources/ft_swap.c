/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:49:22 by dso               #+#    #+#             */
/*   Updated: 2021/12/01 00:00:37 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_stack *stacka, int size)
{
	t_node *first;
	t_node *second;

	if (stacka == NULL || stacka->top->prev == NULL)
		return ;
	first = stacka->top;
	second = stacka->top->prev;
	stacka->top = second;
	first->prev = first->prev->prev;
	first->next = second;	
	stacka->top->prev = first;
	stacka->top->next = NULL;
	if (size == 3)
		stacka->bottom->next = first;
	write(1, "sa", 2);
}

void	ft_sb(t_stack *stackb, int size)
{
	t_node *first;
	t_node *second;

	if (stackb == NULL || stackb->top->prev == NULL)
		return ;
	first = stackb->top;
	second = stackb->top->prev;
	stackb->top = second;
	first->prev = first->prev->prev;
	first->next = second;
	stackb->top->prev = first;
	stackb->top->next = NULL;
	if (size == 3)
		stackb->bottom->next = first;
	write(1, "sb", 2);
}

void	ft_ss(t_stack *stacka, t_stack *stackb, int size)
{
	ft_sa(stacka, size);
	ft_sb(stackb, size);
}