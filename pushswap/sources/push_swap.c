/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:26 by dso               #+#    #+#             */
/*   Updated: 2021/12/02 23:15:10 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_free(t_stack *stack)
{
	t_node	*tmp;

	if(!stack)
		return ;
	tmp = stack->top;
	while (stack->top != NULL)
	{
		tmp = tmp->prev;
		free(stack->top);
		stack->top = tmp;
	}
	free(stack);
}

int main(int argc, char **argv)
{
	t_stack *stacka;
	t_stack *stackb;
	t_node	*tmp;
	int 	size;

	if (argc < 2)
		return (-1);
	stacka = ft_initstack();
	stackb = ft_initstack();
	if (!stacka || !stackb)
		return (-1);
	if (ft_parse(argc, argv, stacka) == 1)
	{
		ft_free(stacka);
		ft_free(stackb);
		write (2, "Error\n", 6);
		return (-1);
	}
	size = ft_stacklen(stacka);
	if (ft_checkorder(stacka) == 1)
	{
		if (size <= 3)
			ft_checkthree(stacka, size);
		else if (size <= 5)
			ft_checkfive(stacka, stackb, size);
		// else if (size <= 100)
		// 	ft_checkmedium(stacka, stackb);
		else
			ft_checkbig(stacka, stackb);
	}

	tmp = stacka->top;
	
	printf("\n");
	while (tmp != NULL)
	{
		printf("a : %d\n", tmp->value);
		tmp = tmp->prev;
	}
	tmp = stackb->top;
	while (tmp != NULL)
	{
		printf("b : %d\n", tmp->value);
		tmp = tmp->prev;
	}
	ft_free(stacka);
	ft_free(stackb);
	return (0);
}