#include "three.h"

// ok
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

// ok
static void	take_forks(t_pool *pool)
{
	sem_wait(pool->twin_lock);
	sem_wait(pool->forks);
	ft_print_time(pool, "has taken a fork");
	sem_wait(pool->forks);
	ft_print_time(pool, "has taken a fork");
	sem_post(pool->twin_lock);
}

// ok
static void	eating(t_pool *pool)
{
	sem_wait(pool->philo->guard);
	ft_print_time(pool, "is eating");
	ft_sleep(pool->philo->time_to_eat);
	pool->philo->cycles--;
	sem_post(pool->philo->guard);
	sem_post(pool->forks);
	sem_post(pool->forks);
}

// ok
static void	sleeping(t_pool *pool)
{
	ft_print_time(pool, "is sleeping");
	ft_sleep(pool->philo->time_to_sleep);
}

// ok
void	*ft_core(void *arg)
{
	t_pool	*pool;

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
