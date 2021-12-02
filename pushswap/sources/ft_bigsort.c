#include "../includes/push_swap.h"


t_node	*ft_index_small(t_stack *stack)
{
	t_node	*tmp;
	t_node	*smallest;
	int		min;

	tmp = stack->top;
	min = INT_MAX;
	while (tmp)
	{
		if (tmp->value < min && tmp->index == 0)
		{
			min = tmp->value;
			smallest = tmp;
		}
		tmp = tmp->prev;
	}
	return (smallest);
}

static int	ft_setindex(t_stack *stacka)
{
	int	i;
	int	length;
	t_node	*tmp;

	i = 1;
	length = 0;
	while (i <= ft_stacklen(stacka))
	{
		tmp = ft_index_small(stacka);
		tmp->index = i;
		i++;
	}
	while (i != 0)
	{
		length++;
		i /= 10;
	}
	return (length);
}

void	ft_checkbig(t_stack *stacka, t_stack *stackb)
{
	t_node	*tmp;
	int		n;
	int		i;

	n = ft_setindex(stacka);
	i = 0;
	while (i < n)
	{
		tmp = stacka->top;
		while (tmp)
		{
			if (tmp->index % 2 == 0)
			{
				tmp->index /= 10;
				ft_pb(stacka, stackb);
			}
			tmp = tmp->prev;
		}
		if (stackb)
		{
			while (ft_stacklen(stackb) != 0)
				ft_pa(stacka, stackb);
		}
		i++;
	}
}