/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:53 by dso               #+#    #+#             */
/*   Updated: 2022/01/10 10:19:59 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define F "has taken a fork\n"

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_list	t_list;

struct s_philo
{
	int				id;
	int				meals;
	int				starttime;
	int				forkl;
	int				forkr;
	pthread_t		thread;
	pthread_t		status;
	t_list			*lst;
};

struct s_list
{
	int				nbphilo;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				nbeat;
	int				timetotal;
	int				end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	t_philo			*philos;
};

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_error(int err);
int		ft_parsing(int argc, char **argv, t_list *arglist);
int		timems(void);
int		ft_threads(t_list *arglist);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);
int		ft_checkmeals(t_philo *philo);
int		ft_cleanmutex(t_list *lst);

#endif