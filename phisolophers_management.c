/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisolophers_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:47:40 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/17 22:09:35 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void	*life_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->current.lass_eat = ges_time_in_ms();
	if (philo->current.id % 2 == 0)
		usleep(philo->metabolism->time_to_eat * 1000);
	while (philo->metabolism->stop_flag == 0)
	{
		pthread_mutex_lock(philo->lefs_fork);
		printf("philo : %d taken lefs_fork\n", philo->current.id);
		pthread_mutex_lock(philo->righs_fork);
		printf("philo : %d taken righs_fork\n", philo->current.id);
		printf("philo : %d is eating\n", philo->current.id);
		philo->current.lass_eat = ges_time_in_ms();
		usleep(philo->metabolism->time_to_eat * 1000);
		philo->current.eas_count++;
		pthread_mutex_unlock(philo->lefs_fork);
		pthread_mutex_unlock(philo->righs_fork);
		printf("philo : %d is sleeping\n", philo->current.id);
		usleep(philo->metabolism->time_to_sleep * 1000);
		printf("philo : %d is thinking\n", philo->current.id);
	}
	return ((void *)0);
}

void	create_philo(t_philo *philo, t_metabolism *meta)
{
	int	i;

	i = 0;
	while (i < meta->number_of_philosophers)
	{
		pthread_mutex_init(&meta->forks[i], NULL);
		philo[i].current.id = i + 1;
		philo[i].current.eas_count = 0;
		philo[i].metabolism = meta;
		i++;
	}
}

void	ses_forkt_and_stars_life_loop(t_philo *philo, t_metabolism *meta)
{
	int	i;

	i = 0;
	while (i < meta->number_of_philosophers)
	{
		meta->stop_flag = 0;
		philo[i].lefs_fork = &meta->forks[i];
		philo[i].righs_fork = &meta->forks[(i + 1)
			% meta->number_of_philosophers];
		pthread_create(&philo[i].thread_id, NULL, &life_loop, &philo[i]);
		i++;
	}
	printf("IMWORKING 2 FINISH\n");
}
