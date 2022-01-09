#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
	long	minus;

	res = 0;
	minus = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
		if (res > 2147483648 && minus == -1)
			return (0);
		else if (res > 2147483647 && minus == 1)
			return (-1);
	}
	return (res * minus);
}

int	timems(void)
{
	int ms;
	struct timeval time;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

int	ft_error(int err)
{
	if (err == 1)
		write(2, "Error: number of arguments\n", 27);
	else if (err == 2)
		write(2, "Memory Allocation Error\n", 24);
	else if (err == 3)
		write (2, "Arguments Error\n", 16);
	else if (err == 4)
		write (1, "Minimum meal is 0 !\n", 20);
	else if (err == 5)
		write (2, "Threads Error\n", 14);
	return (-1);
}

int	ft_checkMeals(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->arglist->nbPhilo)
	{
		if (philo->arglist->philos[i].meals < philo->arglist->nbEat)
			return (0);
		i++;
	}
	return (1);
}