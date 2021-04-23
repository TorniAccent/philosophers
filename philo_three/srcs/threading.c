#include "../includes/three.h"

// ok
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
			sem_wait(pool->philo->guard);
			ft_print_time(pool, "died");
			return (NULL);
		}
	}
	exit(1);
}

static void	*die(void *arg)
{
	t_pool		*pool;

	pool = arg;
	sem_wait(pool->main_lock);
	sem_post(pool->main_lock);
	exit(1);
}

// ok
static int	create_philo(t_pool *pool, int id, t_init *init)
{
	pool[id].philo->start = ft_time();
	pool[id].time = pool[id].philo->start;
	if (pthread_create(&init->twin[id], NULL, death, &pool[id]))
		return (-1);
	if (pthread_detach(init->twin[id]))
		return (-1);
	if (pthread_create(&init->kamikadze[id], NULL, die, &pool[id]))
		return (-1);
	if (pthread_detach(init->kamikadze[id]))
		return (-1);
	return (0);
}

int	ft_threading(t_init *init, int argc, int *val)
{
	t_pool		*pool;
	int			id;

	sem_wait(init->main_lock);
	pool = ft_init_pool(val[0], init);
	if (!pool)
		return (-1);
	id = -1;
	while (++id < val[0])
	{
		init->philo[id] = fork();
		if (init->philo[id] == 0)
		{
			if (ft_init_philo(&pool[id], val, argc, id) == -1)
				return (-1);
			if (create_philo(pool, id, init) == -1)
				return (-1);
			ft_core(&pool[id]);
		}
	}
	id = -1;
	while (++id < val[0])
		if (waitpid(init->philo[id], NULL, WUNTRACED) == -1)
			exit(1);
	sem_wait(init->main_lock);
	free(pool);
	return (0);
}
