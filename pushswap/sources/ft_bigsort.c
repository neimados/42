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
		i /= 2;
	}
	return (length);
}

void	ft_checkbig(t_stack *stacka, t_stack *stackb)
{
	t_node	*tmp;
	int		n;
	int		i;
	int		j;
	int		size;

	n = ft_setindex(stacka);
	i = 0;
	j = 0;
	size = 0;
	tmp = stacka->top;
	while (i < n)
	{
		size = ft_stacklen(stacka);
		while (j < size)
		{
			if (stacka->top->index % 2 == 0)
			{
				stacka->top->index /= 2;
				ft_pb(stacka, stackb);
			}
			else
			{
				stacka->top->index /= 2;
				ft_ra(stacka);
			}
			j++;
		}
		while (ft_stacklen(stackb) != 0)
			ft_pa(stacka, stackb);
		i++;
		j = 0;
	}
}