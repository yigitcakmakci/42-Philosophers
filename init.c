/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:20:26 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/26 10:15:39 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_metabolism	get_meta(char **argv)
{
	t_metabolism	meta;

	meta.number_of_philosophers = ft_atoi(argv[1]);
	meta.time_to_die = ft_atoi(argv[2]);
	meta.time_to_eat = ft_atoi(argv[3]);
	meta.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		meta.rfn = ft_atoi(argv[5]);
	else
		meta.rfn = -1;
	meta.forks = malloc(sizeof(pthread_mutex_t) * meta.number_of_philosophers);
	meta.stop_flag = 0;
	return (meta);
}

void	create_philo(t_philo *philo, t_metabolism *meta)
{
	int	i;

	pthread_mutex_init(&meta->dead_lock, NULL);
	pthread_mutex_init(&meta->print_mutex, NULL);
	i = 0;
	while (i < meta->number_of_philosophers)
	{
		pthread_mutex_init(&meta->forks[i], NULL);
		philo[i].current.id = i + 1;
		philo[i].current.eat_count = 0;
		philo[i].metabolism = meta;
		i++;
	}
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
