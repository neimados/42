/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:09:49 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:09:50 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_checkorder(t_stack *stacka)
{
	t_node	*tmp;

	tmp = stacka->top;
	while (tmp->prev != NULL)
	{
		if (tmp->value > tmp->prev->value)
			return (1);
		tmp = tmp->prev;
	}
	return (0);
}

int	ft_findbig(t_stack *stacka)
{
	t_node	*tmp;
	int		max;

	tmp = stacka->top;
	max = INT_MIN;
	while (tmp)
	{
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->prev;
	}
	return (max);
}

int	ft_findsmall(t_stack *stacka)
{
	t_node	*tmp;
	int		min;

	tmp = stacka->top;
	min = INT_MAX;
	while (tmp)
	{
		if (tmp->value < min)
			min = tmp->value;
		tmp = tmp->prev;
	}
	return (min);
}
