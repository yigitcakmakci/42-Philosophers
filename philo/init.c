/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:20:26 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 14:58:28 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
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
	meta.forks = NULL;
	meta.stop_flag = 0;
	return (meta);
}

static int	setup_error(t_metabolism *meta, t_philo *philo, char *msg)
{
	if (meta->forks)
		free(meta->forks);
	if (philo)
		free(philo);
	printf("%s\n", msg);
	return (1);
}

int	init_simulation(t_philo **philo, t_metabolism *meta, char **argv)
{
	*meta = get_meta(argv);
	meta->forks = malloc(sizeof(pthread_mutex_t)
			* meta->number_of_philosophers);
	if (!meta->forks)
		return (setup_error(meta, NULL, "Error: Malloc failed for forks"));
	*philo = malloc(sizeof(t_philo) * meta->number_of_philosophers);
	if (!*philo)
		return (setup_error(meta, NULL, "Error: Malloc failed for philos"));
	if (create_philo(*philo, meta) != 0)
		return (setup_error(meta, *philo, "Error: Mutex init failed"));
	init_philos(*philo, meta);
	if (start_simulation(*philo, meta) != 0)
		return (setup_error(meta, *philo, "Error: Thread creation failed"));
	return (0);
}
