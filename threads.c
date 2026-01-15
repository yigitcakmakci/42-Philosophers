/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:02:49 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 15:08:38 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_global_mutexes(t_metabolism *meta)
{
	if (pthread_mutex_init(&meta->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&meta->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&meta->dead_lock);
		return (1);
	}
	return (0);
}

int	create_philo(t_philo *philo, t_metabolism *meta)
{
	int	i;

	if (init_global_mutexes(meta) != 0)
		return (1);
	i = 0;
	while (i < meta->number_of_philosophers)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&meta->forks[i]);
			pthread_mutex_destroy(&meta->dead_lock);
			pthread_mutex_destroy(&meta->print_mutex);
			return (1);
		}
		philo[i].current.id = i + 1;
		philo[i].current.eat_count = 0;
		philo[i].metabolism = meta;
		i++;
	}
	return (0);
}

void	init_philos(t_philo *philo, t_metabolism *meta)
{
	int	i;

	i = 0;
	while (i < meta->number_of_philosophers)
	{
		philo[i].left_fork = &meta->forks[i];
		philo[i].right_fork = &meta->forks[(i + 1)
			% meta->number_of_philosophers];
		philo[i].current.last_eat = get_time_in_ms();
		i++;
	}
}

int	start_simulation(t_philo *philo, t_metabolism *meta)
{
	int	i;

	i = 0;
	meta->start_time = get_time_in_ms();
	while (i < meta->number_of_philosophers)
	{
		philo[i].current.last_eat = meta->start_time;
		if (pthread_create(&philo[i].thread_id, NULL, &life_loop,
				&philo[i]) != 0)
		{
			change_stop_flag(meta);
			while (--i >= 0)
				pthread_join(philo[i].thread_id, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}
