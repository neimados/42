/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:14:40 by dso               #+#    #+#             */
/*   Updated: 2021/12/04 17:17:44 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_checkfail(int minus, t_stack *stack, long nb)
{
	if (minus > 1)
		return (1);
	if (ft_checkargs(nb, stack) == 1)
		return (1);
	if (!ft_push_bottom(stack, nb))
	{
		ft_free(stack);
		return (1);
	}
	return (0);
}

int	ft_checkone(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != ' ' && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
}
