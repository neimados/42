#include "../includes/philo.h"

static void	ft_oneEating(t_philo *philo)
{
	int	eatingTime;

	eatingTime = 0;
	printf("%d\t%d has taken a fork\n", (timems() - philo->arglist->timeTotal), philo->id);
	philo->startTime = timems();
	while (eatingTime < philo->arglist->timeToDie)
	{
		usleep(1000);
		eatingTime = timems() - philo->startTime;
	}
	printf("%d\t%d died\n", (timems() - philo->arglist->timeTotal), philo->id);
	philo->arglist->end = 1;
}

static void	ft_eatingLoop(t_philo *philo)
{
	int	eatingTime;

	eatingTime = timems() - philo->startTime;
	while (eatingTime < philo->arglist->timeToEat && philo->arglist->end != 1)
	{
		usleep(1000);
		eatingTime = timems() - philo->startTime;
	}
}

void	ft_eating(t_philo *philo)
{
	if (philo->arglist->nbPhilo == 1)
	{
		ft_oneEating(philo);
		return ;
	}
	usleep(2000);
	pthread_mutex_lock(&philo->arglist->forks[philo->forkL]);
	if (philo->arglist->end != 1)
		printf("%d\t%d has taken a fork\n", (timems() - philo->arglist->timeTotal), philo->id);
	usleep(2000);
	pthread_mutex_lock(&philo->arglist->forks[philo->forkR]);
	if (philo->arglist->end != 1)
		printf("%d\t%d has taken a fork\n", (timems() - philo->arglist->timeTotal), philo->id);
	usleep(2000);
	if (philo->arglist->end != 1)
		printf("%d\t%d is eating\n", (timems() - philo->arglist->timeTotal), philo->id);
	philo->startTime = timems();
	ft_eatingLoop(philo);
	pthread_mutex_unlock(&philo->arglist->forks[philo->forkL]);
	pthread_mutex_unlock(&philo->arglist->forks[philo->forkR]);
	philo->meals += 1;
}

void	ft_sleeping(t_philo *philo)
{
	int	sleepTime;

	sleepTime = timems();
	usleep(8000);
	if (philo->arglist->end != 1)
		printf("%d\t%d is sleeping\n", (timems() - philo->arglist->timeTotal), philo->id);
	while(timems() < sleepTime + philo->arglist->timeToSleep && philo->arglist->end != 1)
		usleep(1000);
}

void	ft_thinking(t_philo *philo)
{
	usleep(8000);
	if (philo->arglist->end != 1)
		printf("%d\t%d is thinking\n", (timems() - philo->arglist->timeTotal), philo->id);
}