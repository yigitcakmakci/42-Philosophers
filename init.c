/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:20:26 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 13:15:48 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

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

static int	init_global_mutexes(t_metabolism *meta)
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

static int	create_philo(t_philo *philo, t_metabolism *meta)
{
	int	i;

	if (init_global_mutexes(meta) != 0)
		return (1);
	i = 0;
	while (i < meta->number_of_philosophers)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				free(&meta->forks[i]);
				i--;
			}
			return (1);
		}
		philo[i].current.id = i + 1;
		philo[i].current.eat_count = 0;
		philo[i].metabolism = meta;
		i++;
	}
	return (0);
}

static void	init_philos(t_philo *philo, t_metabolism *meta)
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

int	init_simulation(t_philo **philo, t_metabolism *meta, char **argv)
{
	*meta = get_meta(argv);
	if (!meta->forks)
	{
		printf("Error: Malloc failed for forks\n");
		return (1);
	}
	*philo = malloc(sizeof(t_philo) * meta->number_of_philosophers);
	if (!*philo)
	{
		printf("Error: Malloc failed for philos\n");
		free(meta->forks);
		return (1);
	}
	if (create_philo(*philo, meta) != 0)
	{
		printf("Error: Mutex init failed\n");
		free(*philo);
		free(meta->forks);
		return (1);
	}
	init_philos(*philo, meta);
	if (start_simulation(*philo, meta) != 0)
	{
		free(*philo);
		free(meta->forks);
		return (1);
	}
	return (0);
}
