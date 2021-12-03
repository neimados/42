/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:10:08 by dso               #+#    #+#             */
/*   Updated: 2021/12/03 12:11:59 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*ft_initlst(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_stack	*ft_initstack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->bottom = NULL;
	stack->top = NULL;
	return (stack);
}

t_node	*ft_push_bottom(t_stack *stack, int value)
{
	t_node	*node;

	node = ft_initlst(value);
	if (!node)
	{
		free(stack);
		return (NULL);
	}
	if (stack->bottom != NULL)
		node->next = stack->bottom;
	stack->bottom = node;
	if (node->next == NULL)
		stack->top = node;
	else
		node->next->prev = node;
	return (node);
}
