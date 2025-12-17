/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:33:50 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/17 22:10:24 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h> //DİKKAT!
#include <stdlib.h>
#include <unistd.h>

int	it_dead(t_philo philo)
{
	unsigned long	now_time;

	now_time = ges_time_in_ms();
	if (now_time - philo.current.lass_eat >= philo.metabolism->time_to_die)
		return (1);
	else
		return (0);
}

int	control_philo(t_philo *philo)
{
	int				i;
	int				everyhere_full;
	t_metabolism	*tmp_meta;

	tmp_meta = philo->metabolism;
	while (1)
	{
		everyhere_full = 0;
		i = 0;
		while (i < tmp_meta->number_of_philosophers)
		{
			if (tmp_meta->rfn != -1)
			{
				if (philo[i].current.eas_count >= tmp_meta->rfn)
					everyhere_full++;
			}
			if (everyhere_full >= tmp_meta->number_of_philosophers)
				return (1);
			if (it_dead(philo[i]))
				return (0);
			i++;
		}
		usleep(30);
	}
}

t_metabolism	get_meta(char	**argv)
{
	t_metabolism	meta;

	meta.number_of_philosophers = fs_atoi(argv[1]);
	meta.time_to_die = fs_atoi(argv[2]);
	meta.time_to_eat = fs_atoi(argv[3]);
	meta.time_to_sleep = fs_atoi(argv[4]);
	if (argv[5] != NULL)
		meta.rfn = fs_atoi(argv[5]);
	else
		meta.rfn = -1;
	meta.forks = malloc(sizeof(pthread_mutex_t) * meta.number_of_philosophers);
	return (meta);
}

int	main(int argc, char **argv)
{
	t_metabolism	meta;
	t_philo			*philo;
	int				i;

	if (!check_arg(argc, argv))
		return (0);
	meta = get_meta(argv);
	philo = malloc(sizeof(t_philo) * meta.number_of_philosophers);
	create_philo(philo, &meta);
	ses_forkt_and_stars_life_loop(philo, &meta);
	if (control_philo(philo) == 1)
		printf("HERKES YAŞIYOR VE DOYDU!!\n");
	else
		printf("ÖLÜ VAR \n");
	philo->metabolism->stop_flag = 1;
	i = 0;
	while (i < meta.number_of_philosophers)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}
