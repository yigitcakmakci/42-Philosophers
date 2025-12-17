#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct t_metabolism
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				required_food_number;
	int				stop_flag;
	pthread_mutex_t	*forks;
}					s_metabolism;

typedef struct t_current
{
	int				id;
	unsigned long	last_eat;
	int				eat_count;
}					s_current;

typedef struct t_philo
{
	pthread_t		thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	s_metabolism	*metabolism;
	s_current		current;
}					s_philo;

int					check_arg(char **argv);
int					ft_atoi(const char *str);
unsigned long		get_time_in_ms(void);

#endif