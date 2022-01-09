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

static int	ft_checkinfos(int argc, t_list *arglist)
{
	if (arglist->nbPhilo <= 0 || arglist->timeToDie <= 0
	|| arglist->timeToEat <= 0 || arglist->timeToSleep <=0)
		return (1);
	if (argc == 6)
	{
		if (arglist->nbEat <= 0)
			return(1);
	}
	return (0);
}

static int	ft_initmutex(t_list *arglist)
{
	int	i;

	i = 0;
	arglist->forks = malloc(sizeof(pthread_mutex_t) * arglist->nbPhilo);
	if (!arglist->forks)
		return (1);
	while (i < arglist->nbPhilo)
	{
		if (pthread_mutex_init(&arglist->forks[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&arglist->forks[i]);
				i--;
			}
			free (arglist->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_parsing(int argc, char **argv, t_list *arglist)
{
	if (ft_checkargs(argv) == 1)
		return (1);
	arglist->nbPhilo = ft_atoi(argv[1]);
	arglist->timeToDie = ft_atoi(argv[2]);
	arglist->timeToEat = ft_atoi(argv[3]);
	arglist->timeToSleep = ft_atoi(argv[4]);
	arglist->timeTotal = 0;
	arglist->end = 0;
	if (pthread_mutex_init(&arglist->dead, NULL) != 0)
			return (1);
	if (argc == 6)
		arglist->nbEat = ft_atoi(argv[5]);
	if (ft_checkinfos(argc, arglist) == 1)
		return (1);
	if (ft_initmutex(arglist) == 1)
		return (1);
	return (0);
}
