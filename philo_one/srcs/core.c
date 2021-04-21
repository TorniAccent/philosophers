#include "one.h"

static void	ft_sleep(long i)
{
	struct timeval	time;
	struct timeval	time1;

	gettimeofday(&time, NULL);
	i = i + (time.tv_sec * 1000000) + time.tv_usec;
	while (1)
	{
		usleep(1000);
		gettimeofday(&time1, NULL);
		if ((time1.tv_sec * 1000000) + time1.tv_usec > i)
			break ;
	}
}

static void	take_forks(t_shrmem *stat)
{
	pthread_mutex_lock(&stat->forks[stat->philo->left]);
	ft_print_time(stat, 0, "has taken a fork");
	if (g_the_end == 1)
		return ;
	pthread_mutex_lock(&stat->forks[stat->philo->right]);
	ft_print_time(stat, 0, "has taken a fork");
	if (g_the_end == 1)
		return ;
}

static void	eating(t_shrmem *stat)
{
	pthread_mutex_lock(&stat->philo->guard);
	ft_print_time(stat, 0, "is eating");
	if (g_the_end == 1)
		return ;
	ft_sleep(stat->philo->eat * 1000);
	stat->philo->cicles--;
	pthread_mutex_unlock(&stat->philo->guard);
	pthread_mutex_unlock(&stat->forks[stat->philo->right]);
	pthread_mutex_unlock(&stat->forks[stat->philo->left]);
}

static void	sleeping(t_shrmem *stat)
{
	ft_print_time(stat, 0, "is sleeping");
	if (g_the_end == 1)
		return ;
	ft_sleep(stat->philo->sleep * 1000);
}

void	*ft_core(void *arg)
{
	t_shrmem		*stat;

	stat = arg;
	stat->philo->start = ft_time();
	while (stat->philo->cicles != 0)
	{
		take_forks(stat);
		if (g_the_end == 1)
			return (NULL);
		stat->philo->start = ft_time();
		eating(stat);
		if (g_the_end == 1)
			return (NULL);
		sleeping(stat);
		if (g_the_end == 1)
			return (NULL);
		ft_print_time(stat, 0, "is thinking");
		if (g_the_end == 1)
			return (NULL);
	}
	return (NULL);
}