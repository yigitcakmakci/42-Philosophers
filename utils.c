/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:52:10 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/17 10:12:38 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

unsigned long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	safe_print(t_philo *philo, int status)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->metabolism->print_mutex);
	pthread_mutex_lock(&philo->metabolism->dead_lock);
	if (philo->metabolism->stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->metabolism->dead_lock);
		pthread_mutex_unlock(&philo->metabolism->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->metabolism->dead_lock);
	time = get_time_in_ms() - philo->metabolism->start_time;
	if (status == 1)
		printf("%lu %d has taken a fork\n", time, philo->current.id);
	else if (status == 2)
		printf("%lu %d is eating\n", time, philo->current.id);
	else if (status == 3)
		printf("%lu %d is sleeping\n", time, philo->current.id);
	else if (status == 4)
		printf("%lu %d is thinking\n", time, philo->current.id);
	else if (status == 5)
		printf("%lu %d died\n", time, philo->current.id);
	pthread_mutex_unlock(&philo->metabolism->print_mutex);
}
