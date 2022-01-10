/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:20:07 by dso               #+#    #+#             */
/*   Updated: 2022/01/10 11:45:51 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_status(void *philos)
{
	t_philo	*ph;
	int		tmp;

	ph = philos;
	tmp = 0;
	pthread_mutex_lock(&ph->lst->dead);
	while (ph->lst->end != 1 && ph->lst->nbphilo != 1)
	{
		if (timems() - ph->starttime >= ph->lst->timetodie)
		{
			tmp = timems() - ph->lst->timetotal;
			printf("%d\t%d died\n", tmp, ph->id);
			ph->lst->end = 1;
			pthread_mutex_unlock(&ph->lst->dead);
			return (NULL);
		}
		usleep(100);
	}
	pthread_mutex_unlock(&ph->lst->dead);
	return (NULL);
}

void	*ft_actions(void *philos)
{
	t_philo	*ph;

	ph = philos;
	if (ph->id % 2 == 0)
		usleep(1000 * ph->lst->timetoeat);
	while (ph->lst->end != 1)
	{
		if (ph->lst->end != 1)
			ft_eating(ph);
		if (ph->lst->nbeat != -1)
		{
			if (ft_checkmeals(ph) == 1)
			{
				ph->lst->end = 1;
				return (NULL);
			}
		}
		if (ph->lst->end != 1)
			ft_sleeping(ph);
		if (ph->lst->end != 1)
			ft_thinking(ph);
	}
	return (NULL);
}

static int	ft_jointhreads(t_list *lst)
{
	int	i;

	i = 0;
	while (i < lst->nbphilo)
	{
		if (pthread_join(lst->philos[i].thread, NULL) != 0
			|| pthread_join(lst->philos[i].status, NULL) != 0)
			return (ft_cleanmutex(lst));
		i++;
	}
	return (0);
}

static int	ft_initphilo(t_list *lst)
{
	int	i;

	i = -1;
	while (++i < lst->nbphilo)
	{
		lst->philos[i].id = i + 1;
		lst->philos[i].meals = 0;
		lst->philos[i].starttime = timems();
		lst->philos[i].forkl = i;
		lst->philos[i].forkr = (i + 1) % lst->nbphilo;
		lst->philos[i].lst = lst;
		if (pthread_create(&lst->philos[i].thread, NULL, \
			ft_actions, &lst->philos[i]) != 0
			|| pthread_create(&lst->philos[i].status, NULL, \
				ft_status, &lst->philos[i]) != 0)
			return (ft_cleanmutex(lst));
	}
	return (0);
}

int	ft_threads(t_list *lst)
{
	lst->timetotal = timems();
	lst->philos = malloc(sizeof(t_philo) * lst->nbphilo);
	if (!lst->philos)
		return (1);
	if (ft_initphilo(lst) == 1)
		return (1);
	if (ft_jointhreads(lst) == 1)
		return (1);
	return (0);
}
