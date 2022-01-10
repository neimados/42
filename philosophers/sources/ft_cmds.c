/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:59 by dso               #+#    #+#             */
/*   Updated: 2022/01/10 11:49:16 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_oneeating(t_philo *ph)
{
	int	eatingtime;

	eatingtime = 0;
	printf("%d\t%d has taken a fork\n", (timems() - ph->lst->timetotal), ph->id);
	ph->starttime = timems();
	while (eatingtime < ph->lst->timetodie)
	{
		usleep(1000);
		eatingtime = timems() - ph->starttime;
	}
	printf("%d\t%d died\n", (timems() - ph->lst->timetotal), ph->id);
	ph->lst->end = 1;
}

static void	ft_eatingloop(t_philo *ph)
{
	int	eatingtime;

	eatingtime = timems() - ph->starttime;
	while (eatingtime < ph->lst->timetoeat && ph->lst->end != 1)
	{
		usleep(1000);
		eatingtime = timems() - ph->starttime;
	}
}

void	ft_eating(t_philo *ph)
{
	if (ph->lst->nbphilo == 1)
	{
		ft_oneeating(ph);
		return ;
	}
	usleep(1000);
	pthread_mutex_lock(&ph->lst->forks[ph->forkl]);
	if (ph->lst->end != 1)
		printf("%d\t%d "F, (timems() - ph->lst->timetotal), ph->id);
	usleep(1000);
	pthread_mutex_lock(&ph->lst->forks[ph->forkr]);
	if (ph->lst->end != 1)
		printf("%d\t%d "F, (timems() - ph->lst->timetotal), ph->id);
	usleep(1000);
	if (ph->lst->end != 1)
		printf("%d\t%d is eating\n", (timems() - ph->lst->timetotal), ph->id);
	ph->starttime = timems();
	ft_eatingloop(ph);
	pthread_mutex_unlock(&ph->lst->forks[ph->forkl]);
	pthread_mutex_unlock(&ph->lst->forks[ph->forkr]);
	ph->meals += 1;
}

void	ft_sleeping(t_philo *ph)
{
	int	sleeptime;

	sleeptime = timems();
	usleep(1000);
	if (ph->lst->end != 1)
		printf("%d\t%d is sleeping\n", (timems() - ph->lst->timetotal), ph->id);
	while (timems() < sleeptime + ph->lst->timetosleep && ph->lst->end != 1)
		usleep(1000);
}

void	ft_thinking(t_philo *ph)
{
	usleep(1000);
	if (ph->lst->end != 1)
		printf("%d\t%d is thinking\n", (timems() - ph->lst->timetotal), ph->id);
}
