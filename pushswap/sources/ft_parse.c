#include "../includes/push_swap.h"

int	ft_parse(int argc, char **argv, t_stack *stack)
{
	int		i;
	int		j;
	long	nb;

	i = 1;
	j = 0;
	nb = 0;
	if (argc < 2)
		return (1);
	else
	{
		while (i < argc)
		{
			while (argv[i][j])
			{
				nb *= 10;
				nb += argv[i][j] - '0';
				j++;
			}
			ft_push_top(stack, nb);
			nb = 0;
			i++;
			j = 0;
		}
	}
	return (0);
}