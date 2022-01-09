#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo t_philo;
typedef struct s_list t_list;

struct s_philo
{
	int				id;
	int				meals;
	int				startTime;
	int				forkL;
	int				forkR;
	pthread_t		thread;
	pthread_t		status;
	t_list			*arglist;
};

struct s_list
{
	int				nbPhilo;
	int				timeToDie;
	int				timeToEat;
	int				timeToSleep;
	int				nbEat;
	int				timeTotal;
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
int		ft_checkMeals(t_philo *philo);

#endif