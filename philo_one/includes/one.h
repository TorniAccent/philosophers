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

typedef struct	s_ph
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

typedef struct	s_shrmem
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*guard;
	long				time;
	int					phils;
	t_ph				*philo;
}				t_shrmem;

typedef struct	s_init
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*guard;
	pthread_t			*philo;
	pthread_t			*add;
}				t_init;

void			*philo_one(void *arg);

int				threading(t_init *init, int argc, int *val);

void			ft_perror(char *str);
int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				init_philo(t_shrmem *stat, int *val, int argc, int b);
t_shrmem		*init_env(int *val, t_init *init);
void			print_time(t_shrmem *stat, long i, char *str);
t_init			*main_init(int *val, t_init *init);
int				deinit(t_init *init, int *val);
long			chrono(void);

int				*check_args(int argc, char **argv);

#endif
