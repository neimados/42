/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:20:16 by dso               #+#    #+#             */
/*   Updated: 2022/01/10 10:20:17 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_cleanmutex(t_list *lst)
{
	int	i;

	i = 0;
	while (i < lst->nbphilo)
	{
		pthread_detach(lst->philos[i].thread);
		pthread_detach(lst->philos[i].status);
		i++;
	}
	return (1);
}

void	ft_free(t_list *lst)
{
	int	i;

	i = 0;
	while (i < lst->nbphilo)
	{
		pthread_mutex_destroy(&lst->forks[i]);
		pthread_detach(lst->philos[i].thread);
		pthread_detach(lst->philos[i].status);
		i++;
	}
	pthread_mutex_destroy(&lst->dead);
	free(lst->forks);
	free(lst->philos);
	free(lst);
}

int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (ft_error(2));
	if (ft_parsing(argc, argv, lst) == 1)
	{	
		free(lst);
		return (ft_error(3));
	}
	if (ft_threads(lst) == 1)
	{
		ft_free(lst);
		return (ft_error(5));
	}
	ft_free(lst);
	return (0);
}
