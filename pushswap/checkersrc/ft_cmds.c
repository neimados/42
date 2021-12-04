/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:36:43 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:36:29 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_sa2(t_stack *stacka, int size)
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
}

void	ft_sb2(t_stack *stackb, int size)
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
}

void	ft_ss2(t_stack *stacka, t_stack *stackb, int size)
{
	ft_sa2(stacka, size);
	ft_sb2(stackb, size);
}

void	ft_ra2(t_stack *stacka)
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

void	ft_rb2(t_stack *stackb)
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
}
