#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>

typedef struct s_node
{
	int				value;
	int				index;
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
t_node	*ft_push_bottom(t_stack *stack, int value);
int		ft_parse(int argc, char **argv, t_stack *stack);
int		ft_checkargs(long nb, t_stack *stack);
void	ft_sa(t_stack *stacka, int size);
void	ft_sb(t_stack *stackb, int size);
void	ft_ss(t_stack *stacka, t_stack *stackb, int size);
void	ft_pb(t_stack *stacka, t_stack *stackb);
void	ft_pa(t_stack *stacka, t_stack *stackb);
void	ft_ra(t_stack *stacka);
void	ft_rb(t_stack *stackb);
void	ft_rr(t_stack *stacka, t_stack *stackb);
void	ft_rra(t_stack *stacka);
void	ft_rrb(t_stack *stackb);
void	ft_rrr(t_stack *stacka, t_stack *stackb);
int		ft_checkorder(t_stack *stacka);
int		ft_stacklen(t_stack *stack);
void	ft_checkthree(t_stack *stacka, int size);
void	ft_checkfive(t_stack *stacka, t_stack *stackb, int size);
void	ft_checkmedium(t_stack *stacka, t_stack *stackb);
void	ft_checkbig(t_stack *stacka, t_stack *stackb);
int		ft_findbig(t_stack *stacka);
int		ft_findsmall(t_stack *stacka);

#endif