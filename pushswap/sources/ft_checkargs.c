/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:32:06 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 17:23:50 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_checkargs(long nb, t_stack *stack)
{
	t_node	*tmp;
	
	if (nb > INT_MAX || nb < INT_MIN)
		return (1);
	tmp = stack->bottom;
	while (tmp != NULL)
	{
		if (tmp->value == nb)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_stacklen(t_stack *stack)
{
	int		count;
	t_node	*tmp;

	count = 0;
	tmp = stack->top;
	while (tmp)
	{
		count++;
		tmp = tmp->prev;
	}
	return (count);
}