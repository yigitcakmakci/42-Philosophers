/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:33:50 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/26 10:51:14 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	it_number(char *arg)
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
		if (!it_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int start_simulation(t_philo *philo, t_metabolism *meta)
{
    int i = 0;

    meta->start_time = get_time_in_ms();

    while (i < meta->number_of_philosophers)
    {
        philo[i].current.last_eat = meta->start_time;
        
        if (pthread_create(&philo[i].thread_id, NULL, &life_loop, &philo[i]))
            return (1);
        i++;
    }
    return (0);
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
	init_philos(philo, &meta);
	start_simulation(philo, &meta);
	if (control_philo(philo) == 1)
	{
		pthread_mutex_lock(&meta.dead_lock);
		philo->metabolism->stop_flag = 1;
		pthread_mutex_unlock(&meta.dead_lock);
		pthread_mutex_lock(&meta.print_mutex);
		printf("HERKES YAŞIYOR VE DOYDU!!\n");
		pthread_mutex_unlock(&meta.print_mutex);
	}
	else
	{
		pthread_mutex_lock(&meta.dead_lock);
		philo->metabolism->stop_flag = 1;
		pthread_mutex_unlock(&meta.dead_lock);
		pthread_mutex_lock(&meta.print_mutex);
		printf("ÖLÜ VAR \n");
		pthread_mutex_unlock(&meta.print_mutex);
	}
	i = 0;
	while (i < meta.number_of_philosophers)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	free(meta.forks);
	free(philo);
	return (0);
}
