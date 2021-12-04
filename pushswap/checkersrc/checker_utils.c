/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:02:15 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 14:22:34 by dso              ###   ########.fr       */
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
	if (ft_checkorder(stacka) == 0 && ft_stacklen(stackb) == 0)
	{
		write (2, "OK\n", 3);
		return (1);
	}
	return (0);
}

static int	ft_checktask2(char *str, t_stack *jobs)
{
	int	i;

	i = 0;
	if (str[i] == 's' && str[i + 1] == 'a')
		ft_push_bottom(jobs, 1);
	else if (str[i] == 'p' && str[i + 1] == 'a')
		ft_push_bottom(jobs, 2);
	else if (str[i] == 'p' && str[i + 1] == 'b')
		ft_push_bottom(jobs, 3);
	else if (str[i] == 'r' && str[i + 1] == 'a')
		ft_push_bottom(jobs, 4);
	else
		return (1);
	return (0);
}

int	ft_checktask(char *str, t_stack *jobs)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	if (size == 3)
	{
		if (ft_checktask2(str, jobs) == 1)
			return (1);
	}
	else if (size == 4)
	{
		if (str[i] == 'r' && str[i + 1] == 'r' && str[i + 2] == 'a')
			ft_push_bottom(jobs, 5);
		else
			return (1);
	}
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
			ft_pa2(stacka, stackb);
		else if (tmp->value == 3)
			ft_pb2(stacka, stackb);
		else if (tmp->value == 4)
			ft_ra2(stacka);
		else if (tmp->value == 5)
			ft_rra2(stacka);
		tmp = tmp->prev;
	}
}
