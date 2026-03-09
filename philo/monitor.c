/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:52:25 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 14:35:22 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	change_stop_flag(t_metabolism *meta)
{
	pthread_mutex_lock(&(*meta).dead_lock);
	(*meta).stop_flag = 1;
	pthread_mutex_unlock(&(*meta).dead_lock);
}

int	is_dead(t_philo philo)
{
	unsigned long	now_time;
	unsigned long	last_eat_time;

	now_time = get_time_in_ms();
	pthread_mutex_lock(&philo.metabolism->dead_lock);
	last_eat_time = philo.current.last_eat;
	pthread_mutex_unlock(&philo.metabolism->dead_lock);
	if (now_time - last_eat_time >= philo.metabolism->time_to_die)
		return (1);
	else
		return (0);
}

int	is_full(t_metabolism *tmp_meta, int eat_count)
{
	if (tmp_meta->rfn != -1)
	{
		if (eat_count >= tmp_meta->rfn)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	init_eat_count(t_philo *philo, int i)
{
	int	eat_count;

	pthread_mutex_lock(&philo->metabolism->dead_lock);
	eat_count = philo[i].current.eat_count;
	pthread_mutex_unlock(&philo->metabolism->dead_lock);
	return (eat_count);
}

int	control_philo(t_philo *philo)
{
	int				i;
	int				everyhere_full;
	t_metabolism	*tmp_meta;
	int				eat_count;

	tmp_meta = philo->metabolism;
	while (1)
	{
		everyhere_full = 0;
		i = 0;
		while (i < tmp_meta->number_of_philosophers)
		{
			eat_count = init_eat_count(philo, i);
			everyhere_full += is_full(tmp_meta, eat_count);
			if (everyhere_full >= tmp_meta->number_of_philosophers)
				return (1);
			if (is_dead(philo[i]))
			{
				safe_print(&philo[i], 5);
				return (0);
			}
			i++;
		}
		usleep(30);
	}
}
