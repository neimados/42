/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:31:26 by dso               #+#    #+#             */
/*   Updated: 2021/12/05 11:02:31 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

void	ft_push_swap(t_stack *stacka, t_stack *stackb)
{
	int	size;

	size = ft_stacklen(stacka);
	if (size <= 3)
		ft_checkthree(stacka, size);
	else if (size <= 5)
		ft_checkfive(stacka, stackb, size);
	else if (size <= 20)
		ft_checkmedium(stacka, stackb);
	else
		ft_checkbig(stacka, stackb);
}

int	main(int argc, char **argv)
{
	t_stack	*stacka;
	t_stack	*stackb;

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
	if (ft_checkorder(stacka) == 1)
		ft_push_swap(stacka, stackb);
	ft_free(stacka);
	ft_free(stackb);
	return (0);
}
