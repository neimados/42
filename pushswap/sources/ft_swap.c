/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:49:22 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 11:55:15 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_stack *stacka)
{
	t_node *first;
	t_node *second;
	
	if (stacka == NULL || stacka->top->prev == NULL)
		return ;
	first = stacka->top;
	second = stacka->top->prev;
	first->prev = second->prev;
	first->next = second;
	second->next = NULL;
	second->prev = first;
	stacka->top = second;
}

void	ft_sb(t_stack *stackb)
{
	ft_sa(stackb);
}

void	ft_ss(t_stack *stacka, t_stack *stackb)
{
	ft_sa(stacka);
	ft_sb(stackb);
}