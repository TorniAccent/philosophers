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

static void	take_forks(t_pool *pool)
{
	pthread_mutex_lock(&pool->forks[pool->philo->left]);
	ft_print_time(pool, "has taken a fork");
	pthread_mutex_lock(&pool->forks[pool->philo->right]);
	ft_print_time(pool, "has taken a fork");
}

static void	eating(t_pool *pool)
{
	pthread_mutex_lock(&pool->philo->guard);
	ft_print_time(pool, "is eating");
	ft_sleep(pool->philo->time_to_eat * 1000);
	pool->philo->cycles--;
	pthread_mutex_unlock(&pool->philo->guard);
	pthread_mutex_unlock(&pool->forks[pool->philo->right]);
	pthread_mutex_unlock(&pool->forks[pool->philo->left]);
}

static void	sleeping(t_pool *pool)
{
	ft_print_time(pool, "is sleeping");
	ft_sleep(pool->philo->time_to_sleep * 1000);
}

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
