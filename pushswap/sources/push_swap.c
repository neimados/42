/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:26 by dso               #+#    #+#             */
/*   Updated: 2021/11/29 15:16:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int main(int argc, char **argv)
{
	t_stack *stacka;
	t_stack *stackb;
	t_node	*tmp;

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
	// printf("test : %d\n", stacka->top->value);
	// printf("test : %d\n", stacka->bottom->value);
	//ft_sa(stacka);
	//ft_pb(stacka, stackb);
	//ft_ss(stacka, stackb);
	//ft_ra(stacka);
	ft_pb(stacka, stackb);
	ft_pb(stacka, stackb);
	ft_pb(stacka, stackb);
	ft_pb(stacka, stackb);
	// ft_rr(stacka, stackb);
	ft_rrr(stacka, stackb);
	
	tmp = stacka->top;
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