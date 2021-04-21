#ifndef ONE_H
# define ONE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>

int				g_the_end;

typedef struct s_ph
{
	int					id;
	int					start_die;
	long				die;
	int					eat;
	int					sleep;
	int					left;
	int					cicles;
	int					right;
	long				start;
	pthread_mutex_t		guard;
}				t_ph;

typedef struct s_shrmem
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*guard;
	long				time;
	int					phils;
	t_ph				*philo;
}				t_shrmem;

typedef struct s_init
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*guard;
	pthread_t			*philo;
	pthread_t			*add;
}				t_init;

void			*ft_core(void *arg);

int				ft_threading(t_init *init, int argc, int *val);

long			ft_time(void);
int				ft_init_philo(t_shrmem *stat, int *val, int argc, int b);
t_shrmem		*ft_init_pool(int *val, t_init *init);
t_init			*ft_init_init(int *val, t_init *init);
int				ft_destruct(t_init *init, int *val);

void			ft_print_error(char *str);
void			ft_print_time(t_shrmem *stat, long i, char *str);
int				ft_strlen(char *str);
int				ft_atoi(char *str);

int				*ft_parse_args(int argc, char **argv);

#endif
