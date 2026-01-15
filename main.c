/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:33:50 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 13:12:55 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	is_number(char *arg)
{
	int	i;

	if (arg == ((void *)0))
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!((arg[i] <= '9') && (arg[i] >= '0')))
		{
			printf("Argüman içerisinde geçersiz karakter\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	if (!(argc <= 6 && argc >= 5))
	{
		printf("ARGÜMAN SAYISI GEÇERSİZ\n");
		return (0);
	}
	i = 1;
	while (argv[i] && i < 5)
	{
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
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
			return (1);
		i++;
	}
	return (0);
}

void	change_stop_flag(t_metabolism *meta)
{
	pthread_mutex_lock(&(*meta).dead_lock);
	(*meta).stop_flag = 1;
	pthread_mutex_unlock(&(*meta).dead_lock);
}

int	main(int argc, char **argv)
{
	t_metabolism	meta;
	t_philo			*philo;

	if (!check_arg(argc, argv))
		return (0);
	if (init_simulation(&philo, &meta, argv) != 0)
		return (1);
	if (control_philo(philo) == 1)
	{
		change_stop_flag(&meta);
		mutex_print(philo, "HERKES YAŞIYOR VE DOYDU");
	}
	else
	{
		change_stop_flag(&meta);
		mutex_print(philo, "ÖLÜ VAR");
	}
	destroy_pthread(philo, meta);
	free(meta.forks);
	free(philo);
	return (0);
}
