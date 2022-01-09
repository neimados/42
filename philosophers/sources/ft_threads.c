#include "../includes/philo.h"

void	*ft_status(void *philos)
{
	t_philo	*philo;

	philo = philos;
	pthread_mutex_lock(&philo->arglist->dead);
	while (philo->arglist->end != 1 && philo->arglist->nbPhilo != 1)
	{
		if (timems() - philo->startTime >= philo->arglist->timeToDie)
		{
			printf("%d\t%d died\n", (timems() - philo->arglist->timeTotal), philo->id);
			philo->arglist->end = 1;
			pthread_mutex_unlock(&philo->arglist->dead);
			return (NULL);
		}
		usleep(100);
	}
	pthread_mutex_unlock(&philo->arglist->dead);
	return (NULL);
}

void	*ft_actions(void *philos)
{
	t_philo	*philo;
	
	philo = philos;
	if (philo->id % 2 == 0)
		usleep(1000 * philo->arglist->timeToEat);
	while (philo->arglist->end != 1)
	{
		if (philo->arglist->end != 1)
			ft_eating(philo);
		if (philo->arglist->nbEat != 0)
		{
			if (ft_checkMeals(philo) == 1)
			{
				philo->arglist->end = 1;
				return (NULL);
			}
		}
		if (philo->arglist->end != 1)
			ft_sleeping(philo);
		if (philo->arglist->end != 1)
			ft_thinking(philo);
	}
	return (NULL);
}

static int	ft_joinThreads(t_list *arglist)
{
	int	i;

	i = 0;
	while (i < arglist->nbPhilo)
	{
		if (pthread_join(arglist->philos[i].thread, NULL) != 0
		|| pthread_join(arglist->philos[i].status, NULL) != 0)
		{
			i = 0;
			while (i < arglist->nbPhilo)
			{
				pthread_detach(arglist->philos[i].thread);
				pthread_detach(arglist->philos[i].status);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_initPhilo(t_list *arglist)
{
	int	i;

	i = -1;
	while (++i < arglist->nbPhilo)
	{
		arglist->philos[i].id = i + 1;
		arglist->philos[i].meals = 0;
		arglist->philos[i].startTime = timems();
		arglist->philos[i].forkL = i;
		arglist->philos[i].forkR = (i + 1) % arglist->nbPhilo;
		arglist->philos[i].arglist = arglist;
		if (pthread_create(&arglist->philos[i].thread, NULL, ft_actions, &arglist->philos[i]) != 0
		|| pthread_create(&arglist->philos[i].status, NULL, ft_status, &arglist->philos[i]) != 0)
		{
			while (i >= 0)
			{
				pthread_detach(arglist->philos[i].thread);
				pthread_detach(arglist->philos[i].status);
				i--;
			}
			free(arglist->philos);
			return (1);
		}
	}
	return (0);
}

int	ft_threads(t_list *arglist)
{
	arglist->timeTotal = timems();
	arglist->philos = malloc(sizeof(t_philo) * arglist->nbPhilo);
	if (!arglist->philos)
		return (1);
	if (ft_initPhilo(arglist) == 1)
		return (1);
	if (ft_joinThreads(arglist) == 1)
		return (1);
	return (0);
}