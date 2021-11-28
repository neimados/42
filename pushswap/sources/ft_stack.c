#include "../includes/push_swap.h"

t_node	*ft_initlst(int value)
{
	t_node *node;
	
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_stack	*ft_initstack(void)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	stack->bottom = NULL;
	stack->top = NULL;
	return (stack);
}

void	ft_push_top(t_stack *stack, int value)
{
	t_node *node;

	node = ft_initlst(value);
	if (!node)
		return ;
	node->prev = stack->top;
	stack->top = node;
	if (node->prev == NULL)//SI LA STACK ETAIT VIDE
		stack->bottom = node;
	else
		node->prev->next = node;//CHANGER LE NEXT DE L ANCIEN TOP
}

void	ft_push_bottom(t_stack *stack, int value)
{
	t_node *node;

	node = ft_initlst(value);
	if (!node)
		return ;
	node->next = stack->bottom;
	stack->bottom = node;
	if (node->next == NULL)
		stack->top = node;
	else
		node->next->prev = node;
}