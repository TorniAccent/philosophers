#include "one.h"

// up
static void	ft_sleep(int ms)
{
	struct timeval	start;
	struct timeval	cool_down;
	long			us;

	gettimeofday(&start, NULL);
	us = (long)ms * (long)1000 + (start.tv_sec * 1000000) + start.tv_usec;
	while (1)
	{
		usleep(1000);
		gettimeofday(&cool_down, NULL);
		if ((cool_down.tv_sec * 1000000) + cool_down.tv_usec > us)
			break ;
	}
}

// up
static void	take_forks(t_pool *pool)
{
	pthread_mutex_lock(&pool->forks[pool->philo->left]);
	ft_print_time(pool, "has taken a fork");
	pthread_mutex_lock(&pool->forks[pool->philo->right]);
	ft_print_time(pool, "has taken a fork");
}

// up
static void	eating(t_pool *pool)
{
	pthread_mutex_lock(&pool->philo->guard);
	ft_print_time(pool, "is eating");
	ft_sleep(pool->philo->time_to_eat);
	pool->philo->cycles--;
	pthread_mutex_unlock(&pool->philo->guard);
	pthread_mutex_unlock(&pool->forks[pool->philo->right]);
	pthread_mutex_unlock(&pool->forks[pool->philo->left]);
}

// up
static void	sleeping(t_pool *pool)
{
	ft_print_time(pool, "is sleeping");
	ft_sleep(pool->philo->time_to_sleep);
}

// up
void	*ft_core(void *arg)
{
	t_pool		*pool;

	pool = arg;
	pool->philo->start = ft_time();
	while (pool->philo->cycles != 0)
	{
		take_forks(pool);
		pool->philo->start = ft_time();
		eating(pool);
		sleeping(pool);
		ft_print_time(pool, "is thinking");
	}
	return (NULL);
}
