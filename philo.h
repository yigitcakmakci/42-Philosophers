/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:07:44 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 14:46:43 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_metabolism
{
	unsigned long	start_time;
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				rfn;
	int				stop_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}					t_metabolism;

typedef struct s_current
{
	int				id;
	unsigned long	last_eat;
	int				eat_count;
}					t_current;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_metabolism	*metabolism;
	t_current		current;
}					t_philo;

int					check_arg(int argc, char **argv);
int					ft_atoi(const char *str);
unsigned long		get_time_in_ms(void);
void				*life_loop(void *arg);
void				set_forks_and_start_life_loop(t_philo *philo,
						t_metabolism *meta);
void				spy_philo(t_philo *philo);
void				safe_print(t_philo *philo, int print_status);
t_metabolism		get_meta(char **argv);
int					control_philo(t_philo *philo);
void				mutex_print(t_philo *philo, char *str);
void				destroy_pthread(t_philo *philo, t_metabolism *meta);
int					init_simulation(t_philo **philo, t_metabolism *meta,
						char **argv);
int					start_simulation(t_philo *philo, t_metabolism *meta);
int					create_philo(t_philo *philo, t_metabolism *meta);
void				init_philos(t_philo *philo, t_metabolism *meta);
void				change_stop_flag(t_metabolism *meta);
void				cleanup_mutexes(t_philo *philo, t_metabolism *meta);

#endif