/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:27:27 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:37:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_rrb2(t_stack *stackb)
{
	t_node	*first;
	t_node	*second;

	if (stackb->top->prev == NULL)
		return ;
	first = stackb->bottom;
	second = stackb->bottom->next;
	second->prev = NULL;
	stackb->bottom = second;
	first->prev = stackb->top;
	first->next = NULL;
	stackb->top->next = first;
	stackb->top = first;
}

void	ft_rrr2(t_stack *stacka, t_stack *stackb)
{
	ft_rra2(stacka);
	ft_rrb2(stackb);
}
