#include "one.h"

static void	*death(void *arg)
{
	t_shrmem			*stat;
	long				ms;

	stat = arg;
	while (stat->philo->cicles != 0)
	{
		usleep(stat->philo->start_die * 1000);
		ms = ft_time();
		if (ms - stat->philo->start >= stat->philo->die)
		{
			pthread_mutex_lock(&stat->guard[7]);
			pthread_mutex_lock(&stat->philo->guard);
			if (stat->philo->cicles == 0)
			{
				pthread_mutex_lock(&stat->guard[3]);
				pthread_mutex_unlock(&stat->guard[0]);
			}
			else
				ft_print_time(stat, ms, "died");
			return (NULL);
		}
	}
	return (NULL);
}

static int	create_philo(t_shrmem *new, int b, t_init *init)
{
	new->philo->start = ft_time();
	if (pthread_create(&init->philo[b], NULL, ft_core, &new[b]) != 0)
		return (-1);
	if (pthread_detach(init->philo[b]) != 0)
		return (-1);
	if (pthread_create(&init->add[b], NULL, death, &new[b]) != 0)
		return (-1);
	if (pthread_detach(init->add[b]) != 0)
		return (-1);
	return (0);
}

static int	even_odd_launch(int *val, t_shrmem *new, t_init *init, int argc)
{
	int		b;

	b = 0;
	while (b < val[0])
	{
		if (ft_init_philo(&new[b], val, argc, b) == -1)
			return (-1);
		create_philo(new, b, init);
		b += 2;
	}
	usleep(100);
	b = 1;
	while (b < val[0])
	{
		if (ft_init_philo(&new[b], val, argc, b) == -1)
			return (-1);
		create_philo(new, b, init);
		b += 2;
	}
	return (0);
}

int	ft_threading(t_init *init, int argc, int *val)
{
	t_shrmem	*new;
	int			b;

	pthread_mutex_lock(&init->guard[0]);
	g_the_end = 0;
	new = ft_init_pool(val, init);
	if (!new)
		return (-1);
	if (even_odd_launch(val, new, init, argc) == -1)
		return (-1);
	pthread_mutex_lock(&init->guard[0]);
	b = -1;
	while (++b < val[0])
	{
		pthread_mutex_destroy(&new[b].philo->guard);
		free(new[b].philo);
	}
	free(new);
	return (0);
}
