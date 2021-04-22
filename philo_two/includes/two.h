#ifndef TWO_H
# define TWO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_ph
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				cycles;
	int				left;
	int				right;
	long			start;
	pthread_mutex_t	guard;
}					t_ph;

typedef struct s_pool
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*philo_lock;
	pthread_mutex_t	*twin_lock;
	pthread_mutex_t	*main_lock;
	long			time;
	t_ph			*philo;
}					t_pool;

typedef struct s_init
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	philo_lock;
	pthread_mutex_t	twin_lock;
	pthread_mutex_t	main_lock;
	pthread_t		*philo;
	pthread_t		*twin;
}					t_init;

void			*ft_core(void *arg);

int				ft_threading(t_init *init, int argc, int *val);

long			ft_time(void);
int				ft_init_philo(t_pool *stat, int *val, int argc, int id);
t_init			*ft_init_init(int nb, t_init *init);
t_pool			*ft_init_pool(int number, t_init *init);
int				ft_destruct(t_init *init, int *val);

void 			*ft_malloc_assign(void **assignment_operand, size_t size);
void			ft_print_error(char *str);
void			ft_print_time(t_pool *stat, char *str);
int				ft_strlen(char *str);
int				ft_atoi(char *str);

int				*ft_parse_args(int argc, char **argv);

#endif
