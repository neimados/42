/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <damien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:21:08 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 23:24:42 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

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
			ft_push_bottom(jobs, 9);
		else if (str[i] == 'r' && str[i + 1] == 'r' && str[i + 2] == 'b')
			ft_push_bottom(jobs, 10);
		else if (str[i] == 'r' && str[i + 1] == 'r' && str[i + 2] == 'r')
			ft_push_bottom(jobs, 11);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	ft_gnl(t_stack *jobs)
{
	char	*str;

	str = get_next_line(0);
	if (str == NULL)
		return (1);
	while (str != NULL)
	{
		if (ft_checktask(str, jobs) == 1)
		{
			free(str);
			write (2, "Error\n", 6);
			return (1);
		}
		free(str);
		str = get_next_line(0);
	}
	free(str);
	return (0);
}

static int	ft_freeall(t_stack *stacka, t_stack *stackb, t_stack *jobs)
{
	if (stacka)
	{
		if (ft_checkorder(stacka) == 0 && ft_stacklen(stackb) == 0)
			write (2, "OK\n", 3);
	}
	ft_free(stacka);
	ft_free(stackb);
	ft_free(jobs);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_stack	*stacka;
	t_stack	*stackb;
	t_stack	*jobs;

	if (argc < 2)
		return (1);
	stacka = ft_initstack();
	stackb = ft_initstack();
	if (!stacka || !stackb)
		return (-1);
	if (ft_checkfirst(argc, stacka, stackb, argv) == 1)
		return (-1);
	jobs = ft_initstack();
	if (ft_gnl(jobs) == 1)
		return (ft_freeall(stacka, stackb, jobs));
	dotask(jobs, stacka, stackb);
	if (ft_checkorder(stacka) == 0 && ft_stacklen(stackb) == 0)
		write (2, "OK\n", 3);
	else
		write (1, "KO\n", 3);
	ft_free(stacka);
	ft_free(stackb);
	return (0);
}
