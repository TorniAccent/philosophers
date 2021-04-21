#include "one.h"

long	ft_time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / (long)1000) + (time.tv_sec * (long)1000));
}

int	ft_init_philo(t_shrmem *stat, int *val, int argc, int b)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	stat->time = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	stat->philo = malloc(sizeof(t_ph));
	if (!stat->philo)
		return (-1);
	stat->philo->id = b + 1;
	stat->philo->start_die = val[1];
	stat->philo->die = val[1];
	stat->philo->eat = val[2];
	stat->philo->sleep = val[3];
	stat->philo->left = b;
	stat->philo->right = b + 1;
	if (pthread_mutex_init(&stat->philo->guard, NULL) != 0)
		return (-1);
	if (b + 1 == val[0])
	{
		if (val[0] != 1)
			stat->philo->right = 0;
	}
	stat->philo->cicles = -1;
	if (argc == 6)
		stat->philo->cicles = val[4];
	return (0);
}

t_shrmem	*ft_init_pool(int *v, t_init *init)
{
	t_shrmem		*new;
	int				i;
	long			m;

	m = ft_time();
	i = 0;
	new = malloc(sizeof(t_shrmem) * (v[0]));
	if (!new)
		return (NULL);
	while (i != v[0])
	{
		new[i].time = m;
		new[i].forks = init->forks;
		new[i].guard = init->guard;
		new[i].phils = v[0];
		i++;
	}
	return (new);
}

t_init	*ft_init_init(int *val, t_init *init)
{
	int		b;

	init->philo = malloc(sizeof(pthread_t) * val[0]);
	if (!init->philo)
		return (NULL);
	init->add = malloc(sizeof(pthread_t) * val[0]);
	if (!init->add)
		return (NULL);
	init->guard = malloc(sizeof(pthread_mutex_t) * 10);
	if (!init->guard)
		return (NULL);
	b = -1;
	while (++b != 10)
		if (pthread_mutex_init(&init->guard[b], NULL) != 0)
			return (NULL);
	init->forks = malloc(sizeof(pthread_mutex_t) * val[0]);
	if (!init->forks)
		return (NULL);
	b = -1;
	while (++b != val[0])
		if (pthread_mutex_init(&init->forks[b], NULL) != 0)
			return (NULL);
	return (init);
}

int	ft_destruct(t_init *init, int *val)
{
	int		b;

	b = -1;
	while (++b < 10)
		pthread_mutex_destroy(&init->guard[b]);
	b = -1;
	while (++b < val[0])
		pthread_mutex_destroy(&init->forks[b]);
	free(val);
	free(init->philo);
	free(init->add);
	free(init->guard);
	free(init->forks);
	free(init);
	return (-1);
}
