/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phisolophers_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:47:40 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/18 11:57:43 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	safe_print(t_philo *philo, int print_status)
{
	unsigned long time;

	time = get_time_in_ms() - philo->metabolism->start_time;
	if (philo->metabolism->stop_flag == 0)
	{
		if (print_status == 1)
			printf("%lu %d has taken a fork\n", time, philo->current.id);
		else if (print_status == 2)
			printf("%lu %d is eating\n", time, philo->current.id);
		else if (print_status == 3)
			printf("%lu %d is sleeping\n", time, philo->current.id);
		else if (print_status == 4)
			printf("%lu %d is thinking\n", time, philo->current.id);
		else if (print_status == 5)
			printf("%lu %d died\n", time, philo->current.id);
	}
}

void	*life_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->current.id % 2 == 0)
		usleep(1000);
	while (philo->metabolism->stop_flag == 0)
	{
		pthread_mutex_lock(philo->lefs_fork);
		safe_print(philo, 1);
		pthread_mutex_lock(philo->righs_fork);
		safe_print(philo, 1);
		safe_print(philo, 2);
		philo->current.last_eat = get_time_in_ms();
		usleep(philo->metabolism->time_to_eat * 1000);
		philo->current.eas_count++;
		pthread_mutex_unlock(philo->lefs_fork);
		pthread_mutex_unlock(philo->righs_fork);
		safe_print(philo, 3);
		usleep(philo->metabolism->time_to_sleep * 1000);
		safe_print(philo, 4);
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

	meta->start_time = get_time_in_ms();
	i = 0;
	while (i < meta->number_of_philosophers)
	{
		philo[i].current.last_eat = get_time_in_ms();
		meta->stop_flag = 0;
		philo[i].lefs_fork = &meta->forks[i];
		philo[i].righs_fork = &meta->forks[(i + 1)
			% meta->number_of_philosophers];
		pthread_create(&philo[i].thread_id, NULL, &life_loop, &philo[i]);
		i++;
	}
}
