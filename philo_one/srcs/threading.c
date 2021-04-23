#include "../includes/one.h"

// ??
static void	*death(void *arg)
{
	t_pool		*pool;
	long		ms;

	pool = arg;
	while (pool->philo->cycles != 0)
	{
		usleep(pool->philo->time_to_die * 1000);
		ms = ft_time() - pool->philo->start;
		if (ms >= pool->philo->time_to_die && pool->philo->cycles != 0)
		{
			pthread_mutex_lock(pool->twin_lock);
			pthread_mutex_lock(&pool->philo->guard);
			ft_print_time(pool, "died");
			return (NULL);
		}
	}
	return (NULL);
}

// ok
static int	create_philo(t_pool *pool, int id, t_init *init)
{
	pool->philo->start = ft_time();
	if (pthread_create(&init->philo[id], NULL, ft_core, &pool[id]))
		return (-1);
	if (pthread_detach(init->philo[id]))
		return (-1);
	if (pthread_create(&init->twin[id], NULL, death, &pool[id]))
		return (-1);
	if (pthread_detach(init->twin[id]))
		return (-1);
	return (0);
}

// ok
static int	even_odd_launch(int *val, t_pool *pool, t_init *init, int argc)
{
	int		id;

	id = 0;
	while (id < val[0])
	{
		if (ft_init_philo(&pool[id], val, argc, id) == -1)
			return (-1);
		create_philo(pool, id, init);
		id += 2;
	}
	usleep(100);
	id = 1;
	while (id < val[0])
	{
		if (ft_init_philo(&pool[id], val, argc, id) == -1)
			return (-1);
		create_philo(pool, id, init);
		id += 2;
	}
	return (0);
}

// ok
int	ft_threading(t_init *init, int argc, int *val)
{
	t_pool		*pool;
	int			id;

	pthread_mutex_lock(&init->main_lock);
	pool = ft_init_pool(val[0], init);
	if (!pool)
		return (-1);
	if (even_odd_launch(val, pool, init, argc) == -1)
		return (-1);
	pthread_mutex_lock(&init->main_lock);
	id = -1;
	while (++id < val[0])
	{
		pthread_mutex_destroy(&pool[id].philo->guard);
		free(pool[id].philo);
	}
	free(pool);
	return (0);
}
