#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h> 
# include <unistd.h> 
# include <stdbool.h> 
# include <limits.h> 
# include <sys/time.h> 

typedef struct s_fork
{
	int				id;
	bool			exist;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	unsigned long	t_to_think;
	unsigned long	t_last_meal;
	unsigned long	t_start;
	int				required_meals;
	int				id;
	bool			stop;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		philo_thread;
	pthread_mutex_t	philo_lock;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	unsigned long	t_to_think;
	unsigned long	t_start;
	int				required_meals;
	unsigned int	n_philo;
	bool			dinner_started;
	bool			is_dead;
	bool			is_fed;
	pthread_mutex_t	access_mutex;
	pthread_mutex_t	log_mutex;
	t_philo			*philo;
	t_fork			*fork;
}	t_table;

bool			ft_isdigit(int c);
bool			is_valid_args(int ac, char **av);
int				ft_atoi(const char *num);
void			ft_eating(t_philo *philo);
void			ft_thinking(t_philo *philo);
void			ft_sleeping(t_philo *philo);
void			ft_stop_dinner(t_table *table);
bool			ft_stop_routine_check(t_philo *philo);
void			ft_create_forks(t_table *table);
void			ft_take_forks(t_philo *philo);
void			ft_create_philo(t_table *table);
void			*ft_run_routine(void *philosopher);
void			ft_exit(t_table *table);
void			ft_philo_died(t_table *table, int id);
void			ft_log_status(t_philo *philo, char *message, unsigned long time);
unsigned long	ft_get_time_ms(void);
unsigned long	ft_get_think_time(t_table *table);
void			ft_wait_until_time(unsigned long delay_ms, t_philo *philo);
bool			ft_init_forks(t_fork *fork, int id);
void			ft_init_table(t_table *table, char **av);
bool			ft_init_philo(t_philo *philo, t_table *table, int id);
long			ft_ato_long(const char *str);
int				ft_error(const char *msg);
void			ft_synch_all_philo(t_philo *philo);

#endif
