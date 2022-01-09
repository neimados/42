#include "../includes/philo.h"

void	ft_free(t_list *arglist)
{
	int	i;

	i = 0;
	while (i < arglist->nbPhilo)
	{
		pthread_mutex_destroy(&arglist->forks[i]);
		pthread_detach(arglist->philos[i].thread);
		pthread_detach(arglist->philos[i].status);
		i++;
	}
	pthread_mutex_destroy(&arglist->dead);
	free(arglist->forks);
	free(arglist->philos);
	free(arglist);
}

int main (int argc, char **argv)
{
	t_list *arglist;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	arglist = malloc(sizeof(t_list));
	if (!arglist)
		return (ft_error(2));
	if (ft_parsing(argc, argv, arglist) == 1)
	{	
		free(arglist);
		return (ft_error(3));
	}
	if (ft_threads(arglist) == 1)
	{
		ft_free(arglist);
		return (ft_error(5));
	}
	ft_free(arglist);
	return (0);
}