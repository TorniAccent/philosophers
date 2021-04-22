#include "three.h"

// ok
long	ft_time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

int	ft_init_philo(t_pool *pool, int *val, int argc, int id)
{
	pool->time = ft_time();
	if (!ft_malloc_assign((void **)&pool->philo, sizeof(t_ph)))
		return (-1);
	pool->philo->id = id;
	pool->philo->time_to_die = val[1];
	pool->philo->time_to_eat = val[2];
	pool->philo->time_to_sleep = val[3];
	if ((pool->philo->guard = sem_open("/mm4", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (-1);
	if (sem_unlink("/mm4") == -1)
		return (-1);
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
		pool[i].philo_lock = init->philo_lock;
		pool[i].twin_lock = init->twin_lock;
		pool[i].main_lock = init->main_lock;
	}
	return (pool);
}

// ok
t_init	*ft_init_init(int nb, t_init *init)
{
	if ((init->forks = sem_open("/mfs", O_CREAT, 0644, nb)) == SEM_FAILED)
		return (NULL);
	if ((init->philo_lock = sem_open("/mpl", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (NULL);
	if ((init->twin_lock = sem_open("/mtl", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (NULL);
	if ((init->main_lock = sem_open("/mml", O_CREAT, 0644, 1)) == SEM_FAILED)
		return (NULL);
	if (sem_unlink("/mfs") == -1)
		return (NULL);
	if (sem_unlink("/mpl") == -1)
		return (NULL);
	if (sem_unlink("/mtl") == -1)
		return (NULL);
	if (sem_unlink("/mml") == -1)
		return (NULL);
	if (!ft_malloc_assign((void **)&init->philo, sizeof(pid_t) * nb))
		return (NULL);
//	if (!ft_malloc_assign((void **)&init->twin, sizeof(pid_t) * number))
//		return (NULL);
//	if (!ft_malloc_assign((void **)&init->philo, sizeof(pthread_t) * nb))
//		return (NULL);
	if (!ft_malloc_assign((void **)&init->twin, sizeof(pthread_t) * nb))
		return (NULL);
	if (!ft_malloc_assign((void **)&init->kamikadze, sizeof(pthread_t) * nb))
		return (NULL);
	return (init);
}

// ok
int	ft_destruct(t_init *init, int *val)
{
	if (init)
	{
		free(init->philo);
		free(init->twin);
		free(init->kamikadze);
	}
	free(val);
	return (-1);
}
