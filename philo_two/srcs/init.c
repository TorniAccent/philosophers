#include "two.h"

// ok
long	ft_time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

// ok
int	ft_init_philo(t_pool *pool, int *val, int argc, int id)
{
	pool->time = ft_time();
	if (!ft_malloc_assign((void **)&pool->philo, sizeof(t_ph)))
		return (-1);
	pool->philo->id = id;
	pool->philo->time_to_die = val[1];
	pool->philo->time_to_eat = val[2];
	pool->philo->time_to_sleep = val[3];
	pool->philo->left = id;
	pool->philo->right = id + 1;
	if (pthread_mutex_init(&pool->philo->guard, NULL))
		return (-1);
	if (id + 1 == val[0])
	{
		if (val[0] != 1)
			pool->philo->right = 0;
	}
	pool->philo->cycles = -1;
	if (argc == 6)
		pool->philo->cycles = val[4];
	return (0);
}

// ok
t_pool	*ft_init_pool(int number, t_init *init)
{
	t_pool			*pool;
	long			ms;
	int				i;

	if (!ft_malloc_assign((void **)&pool, sizeof(t_pool) * number))
		return (NULL);
	ms = ft_time();
	i = -1;
	while (++i < number)
	{
		pool[i].time = ms;
		pool[i].forks = init->forks;
		pool[i].philo_lock = &init->philo_lock;
		pool[i].twin_lock = &init->twin_lock;
		pool[i].main_lock = &init->main_lock;
	}
	return (pool);
}

// ok
t_init	*ft_init_init(int nb, t_init *init)
{
	int		fid;

	if (!ft_malloc_assign((void **)&init->forks, sizeof(pthread_mutex_t) * nb))
		return (NULL);
	fid = -1;
	while (++fid < nb)
		if (pthread_mutex_init(&init->forks[fid], NULL))
			return (NULL);
	if (pthread_mutex_init(&init->philo_lock, NULL))
		return (NULL);
	if (pthread_mutex_init(&init->twin_lock, NULL))
		return (NULL);
//	if (!ft_malloc_assign((void **)&init->main_lock, sizeof(pthread_mutex_t)))
//		return (NULL);
	if (pthread_mutex_init(&init->main_lock, NULL))
		return (NULL);
	if (!ft_malloc_assign((void **)&init->philo, sizeof(pthread_t) * nb))
		return (NULL);
	if (!ft_malloc_assign((void **)&init->twin, sizeof(pthread_t) * nb))
		return (NULL);
	return (init);
}

// ok
int	ft_destruct(t_init *init, int *val)
{
	int		b;

	if (init)
	{
		b = -1;
		while (++b < val[0])
			pthread_mutex_destroy(&init->forks[b]);
		free(init->forks);
		free(init->philo);
		free(init->twin);
	}
	free(val);
	return (-1);
}
