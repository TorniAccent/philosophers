#include "one.h"

static void	*death(void *arg)
{
	t_pool			*pool;
	long			ms;

	pool = arg;
	while (pool->philo->cycles != 0)
	{
		usleep(pool->philo->time_to_die * 1000);
		ms = ft_time();
		if (ms - pool->philo->start >= (long)pool->philo->time_to_die)
		{
			pthread_mutex_lock(&pool->guard[7]);
			pthread_mutex_lock(&pool->philo->guard);
			if (pool->philo->cycles == 0)
			{
				pthread_mutex_lock(&pool->guard[3]);
				pthread_mutex_unlock(&pool->guard[0]);
			}
			else
				ft_print_time(pool, "died");
			return (NULL);
		}
	}
	return (NULL);
}

static int	create_philo(t_pool *pool, int b, t_init *init)
{
	pool->philo->start = ft_time();
	if (pthread_create(&init->philo[b], NULL, ft_core, &pool[b]) != 0)
		return (-1);
	if (pthread_detach(init->philo[b]) != 0)
		return (-1);
	if (pthread_create(&init->twin[b], NULL, death, &pool[b]) != 0)
		return (-1);
	if (pthread_detach(init->twin[b]) != 0)
		return (-1);
	return (0);
}

static int	even_odd_launch(int *val, t_pool *pool, t_init *init, int argc)
{
	int		b;

	b = 0;
	while (b < val[0])
	{
		if (ft_init_philo(&pool[b], val, argc, b) == -1)
			return (-1);
		create_philo(pool, b, init);
		b += 2;
	}
	usleep(100);
	b = 1;
	while (b < val[0])
	{
		if (ft_init_philo(&pool[b], val, argc, b) == -1)
			return (-1);
		create_philo(pool, b, init);
		b += 2;
	}
	return (0);
}

int	ft_threading(t_init *init, int argc, int *val)
{
	t_pool		*pool;
	int			b;

	pthread_mutex_lock(&init->guard[0]);
	pool = ft_init_pool(val, init);
	if (!pool)
		return (-1);
	if (even_odd_launch(val, pool, init, argc) == -1)
		return (-1);
	pthread_mutex_lock(&init->guard[0]);
	b = -1;
	while (++b < val[0])
	{
		pthread_mutex_destroy(&pool[b].philo->guard);
		free(pool[b].philo);
	}
	free(pool);
	return (0);
}
