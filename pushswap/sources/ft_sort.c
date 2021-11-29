/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:24:19 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 17:18:06 by dso              ###   ########.fr       */
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