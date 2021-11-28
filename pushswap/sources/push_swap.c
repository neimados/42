#include "../includes/push_swap.h"



int main(int argc, char **argv)
{
	t_stack *stacka;
	t_node	*tmp;

	stacka = ft_initstack();
	
	if (ft_parse(argc, argv, stacka) == 1)
		return (-1);
	// printf("test : %d\n", stacka->top->value);
	// printf("test : %d\n", stacka->bottom->value);
	tmp = stacka->top;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->value);
		tmp = tmp->prev;
	}
	return (0);
}