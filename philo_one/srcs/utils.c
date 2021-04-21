#include "one.h"

void	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	print_time(t_shrmem *stat, long i, char *str)
{
	long			ms1;

	pthread_mutex_lock(&stat->guard[3]);
	if (g_the_end == 1)
		return ;
	ms1 = chrono();
	printf("%ldms %d %s\n", ms1 - stat->time, stat->philo->id, str);
	if (i != 0)
	{
		g_the_end = 1;
		pthread_mutex_unlock(&stat->guard[0]);
		return ;
	}

	pthread_mutex_unlock(&stat->guard[3]);
}

int	ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int		res;
	int		i;
	int		a;

	i = 0;
	res = 0;
	a = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v' \
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		a = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (a * res);
}
