/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:02:33 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/17 10:11:32 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	destroy_pthread(t_philo *philo, t_metabolism *meta)
{
	int	i;

	i = 0;
	while (i < meta->number_of_philosophers)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}

void	cleanup_mutexes(t_philo *philo, t_metabolism *meta)
{
	int	i;

	destroy_pthread(philo, meta);
	i = 0;
	while (i < meta->number_of_philosophers)
	{
		pthread_mutex_destroy(&meta->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&meta->dead_lock);
	pthread_mutex_destroy(&meta->print_mutex);
}
