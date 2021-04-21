#include "one.h"

// up
void	ft_print_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	ft_print_time(t_pool *stat, char *str)
{
	long			ms1;

	pthread_mutex_lock(&stat->guard[3]);
	ms1 = ft_time();
	printf("%ldms %d %s\n", ms1 - stat->time, stat->philo->id, str);
	if (ft_strlen(str) == 4)
	{
		pthread_mutex_unlock(&stat->guard[0]);
		return ;
	}
	pthread_mutex_unlock(&stat->guard[3]);
}

// up
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

// up
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
