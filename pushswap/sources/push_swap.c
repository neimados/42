/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:26 by dso               #+#    #+#             */
/*   Updated: 2021/12/02 00:13:21 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int main(int argc, char **argv)
{
	t_stack *stacka;
	t_stack *stackb;
	t_node	*tmp;
	int 	size;

	stacka = ft_initstack();
	stackb = ft_initstack();
	if (argc < 2)
		return (-1);
	else if (ft_parse(argc, argv, stacka) == 1)
	{
		free(stacka);
		free(stackb);
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
		else if (size <= 100)
			ft_checkhundred(stacka, stackb);
	}

	tmp = stacka->top;
	// printf("\ntop : %d\n", stacka->top->value);
	// printf("bottom : %d\n", stacka->bottom->value);
	
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
	return (0);
}