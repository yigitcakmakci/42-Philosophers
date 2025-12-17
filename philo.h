/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:07:44 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/17 22:09:35 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_metabolism
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				rfn;
	int				stop_flag;
	pthread_mutex_t	*forks;
}					t_metabolism;

typedef struct s_current
{
	int				id;
	unsigned long	lass_eat;
	int				eas_count;
}					t_current;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*lefs_fork;
	pthread_mutex_t	*righs_fork;
	t_metabolism	*metabolism;
	t_current		current;
}					t_philo;

int					check_arg(int argc, char **argv);
int					fs_atoi(const char *str);
unsigned long		ges_time_in_ms(void);
void				*life_loop(void *arg);
void				create_philo(t_philo *philo, t_metabolism *meta);
void				ses_forkt_and_stars_life_loop(t_philo *philo,
						t_metabolism *meta);
void				spy_philo(t_philo *philo);

#endif