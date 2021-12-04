/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:02:15 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 23:32:24 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

int	ft_checkfirst(int argc, t_stack *stacka, t_stack *stackb, char **argv)
{
	if (ft_parse(argc, argv, stacka) == 1)
	{
		ft_free(stacka);
		ft_free(stackb);
		write (2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	ft_checktask2(char *str, t_stack *jobs)
{
	int	i;

	i = 0;
	if (str[i] == 's' && str[i + 1] == 'a')
		ft_push_bottom(jobs, 1);
	else if (str[i] == 's' && str[i + 1] == 'b')
		ft_push_bottom(jobs, 2);
	else if (str[i] == 's' && str[i + 1] == 's')
		ft_push_bottom(jobs, 3);
	else if (str[i] == 'p' && str[i + 1] == 'a')
		ft_push_bottom(jobs, 4);
	else if (str[i] == 'p' && str[i + 1] == 'b')
		ft_push_bottom(jobs, 5);
	else if (str[i] == 'r' && str[i + 1] == 'a')
		ft_push_bottom(jobs, 6);
	else if (str[i] == 'r' && str[i + 1] == 'b')
		ft_push_bottom(jobs, 7);
	else if (str[i] == 'r' && str[i + 1] == 'r')
		ft_push_bottom(jobs, 8);
	else
		return (1);
	return (0);
}

void	dotask(t_stack *jobs, t_stack *stacka, t_stack *stackb)
{
	t_node	*tmp;
	int		size;

	size = ft_stacklen(stacka);
	tmp = jobs->top;
	while (tmp)
	{
		if (tmp->value == 1)
			ft_sa2(stacka, size);
		else if (tmp->value == 2)
			ft_sb2(stackb, size);
		else if (tmp->value == 3)
			ft_ss2(stacka, stackb, size);
		else if (tmp->value == 4)
			ft_pa2(stacka, stackb);
		else if (tmp->value == 5)
			ft_pb2(stacka, stackb);
		else if (tmp->value == 6)
			ft_ra2(stacka);
		else if (tmp->value == 7)
			ft_rb2(stackb);
		else if (tmp->value == 8)
			ft_rr2(stacka, stackb);
		else if (tmp->value == 9)
			ft_rra2(stacka);
		else if (tmp->value == 10)
			ft_rrb2(stackb);
		else if (tmp->value == 11)
			ft_rrr2(stacka, stackb);
		tmp = tmp->prev;
	}
}
