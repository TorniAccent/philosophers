#include "three.h"

// ok
void	*ft_malloc_assign(void **assignment_operand, size_t size)
{
	return (*assignment_operand = malloc(size));
}

// ok
void	ft_print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

// ok
void	ft_print_time(t_pool *pool, char *str)
{
	long		ms;

	sem_wait(pool->philo_lock);
	ms = ft_time();
	printf("%ldms %d %s\n", ms - pool->time, pool->philo->id + 1, str);
	if (ft_strlen(str) == 4)
	{
		sem_post(pool->main_lock);
		return ;
	}
	sem_post(pool->philo_lock);
}

// ok
int	ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i] != '\0')
		;
	return (i);
}

// ok
int	ft_atoi(char *str)
{
	int		res;
	int		i;
	int		a;

	i = 0;
	res = 0;
	a = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		a = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (a * res);
}
