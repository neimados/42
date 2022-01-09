#include "../includes/philo.h"

static int	ft_checkargs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

static int	ft_checkinfos(int argc, t_list *lst)
{
	if (lst->nbphilo <= 0 || lst->timetodie <= 0
		|| lst->timetoeat <= 0 || lst->timetosleep <= 0)
		return (1);
	if (argc == 6)
	{
		if (lst->nbeat <= 0)
			return (1);
	}
	return (0);
}

static int	ft_initmutex(t_list *lst)
{
	int	i;

	i = 0;
	lst->forks = malloc(sizeof(pthread_mutex_t) * lst->nbphilo);
	if (!lst->forks)
		return (1);
	while (i < lst->nbphilo)
	{
		if (pthread_mutex_init(&lst->forks[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&lst->forks[i]);
				i--;
			}
			free (lst->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_parsing(int argc, char **argv, t_list *lst)
{
	if (ft_checkargs(argv) == 1)
		return (1);
	lst->nbphilo = ft_atoi(argv[1]);
	lst->timetodie = ft_atoi(argv[2]);
	lst->timetoeat = ft_atoi(argv[3]);
	lst->timetosleep = ft_atoi(argv[4]);
	lst->timetotal = 0;
	lst->end = 0;
	if (pthread_mutex_init(&lst->dead, NULL) != 0)
		return (1);
	if (argc == 6)
		lst->nbeat = ft_atoi(argv[5]);
	if (ft_checkinfos(argc, lst) == 1)
		return (1);
	if (ft_initmutex(lst) == 1)
		return (1);
	return (0);
}
