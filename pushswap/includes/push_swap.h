#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"
#include <stdio.h>

typedef struct s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node			*bottom;
	t_node			*top;
}	t_stack;

t_node	*ft_initlst(int value);
t_stack	*ft_initstack(void);
void	ft_push_top(t_stack *stack, int value);
void	ft_push_bottom(t_stack *stack, int value);
int		ft_parse(int argc, char **argv, t_stack *stack);

#endif