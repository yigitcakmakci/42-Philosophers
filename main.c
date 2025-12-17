#include "philo.h"
#include <pthread.h>
#include <stdio.h>//DİKKAT!
#include <stdlib.h>
#include <unistd.h>

int is_dead(s_philo philo)
{
	unsigned long now_time = get_time_in_ms();
	printf("aç kalınan süre : %lu || ölmek için gereken aç kalma süresi : %lu \n", now_time - philo.current.last_eat, philo.metabolism->time_to_die);
	if (now_time - philo.current.last_eat >= philo.metabolism->time_to_die)
		return (1);
	else
		return (0);
	
}

void	*life_loop(void *arg)
{
	s_philo	*philo;

	philo = (s_philo *)arg;
	philo->current.last_eat = get_time_in_ms();
	if (philo->current.id % 2 == 0)
        usleep(philo->metabolism->time_to_eat * 1000);
	while (philo->metabolism->stop_flag == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("philo : %d taken left_fork\n", philo->current.id);
		pthread_mutex_lock(philo->right_fork);
		printf("philo : %d taken right_fork\n", philo->current.id);
		printf("philo : %d is eating\n", philo->current.id);
		philo->current.last_eat = get_time_in_ms();
		usleep(philo->metabolism->time_to_eat * 1000);
		philo->current.eat_count++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo : %d is sleeping\n", philo->current.id);
		usleep(philo->metabolism->time_to_sleep * 1000);
		printf("philo : %d is thinking\n", philo->current.id);
	}
	return ((void *)0);
}

s_metabolism	get_meta(char **argv)
{
	s_metabolism	meta;

	meta.number_of_philosophers = ft_atoi(argv[1]);
	meta.time_to_die = ft_atoi(argv[2]);
	meta.time_to_eat = ft_atoi(argv[3]);
	meta.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		meta.required_food_number = ft_atoi(argv[5]);
	else 
		meta.required_food_number = -1;
	return (meta);
}

int control_philo(s_philo *philo)
{
	int i;
	int everyhere_full;

	i = 0;
	while (1)
	{
		printf("IMSINSIDE \n");
		everyhere_full = 0;
		i = 0;
		while (i < philo->metabolism->number_of_philosophers)
		{
			printf("philo[%d].current.eat_count : %d\n", i,  philo[i].current.eat_count);
			if (philo->metabolism->required_food_number != -1)
			{
				if (philo[i].current.eat_count >= philo->metabolism->required_food_number)
					everyhere_full++;
			}
			if (everyhere_full >= philo->metabolism->number_of_philosophers)
				return (1);
			if (is_dead(philo[i]))
				return (0);
			i++;
		}
		usleep(30);
	}
}

void	create_philo(s_philo **philo, s_metabolism meta)
{
	int	i;

	i = 0;
	while (i < meta.number_of_philosophers)
	{
		pthread_mutex_init(&meta.forks[i], NULL);
		(*philo)[i].current.id = i + 1;
		(*philo)[i].current.eat_count = 0;
		(*philo)[i].metabolism = &meta;
		i++;
	}
}

void	set_forks_and_start_life_loop(s_philo ** philo, s_metabolism meta)
{
	int	i;

	i = 0;
	while (i < meta.number_of_philosophers)
	{
		meta.stop_flag = 0;
		(*philo)[i].left_fork = &meta.forks[i];
		(*philo)[i].right_fork = &meta.forks[(i + 1) % meta.number_of_philosophers];
		printf("IMWORKING2.1\n");
		pthread_create(&(*philo)[i].thread_id, NULL, &life_loop, &philo[i]);
		i++;
	}
	printf("IMWORKING 2 FINISH\n");
}

int	main(int argc, char **argv)
{
	s_metabolism	meta;
	s_philo			*philo;
	int				i;
	i = 0;
	if (!(argc <= 6 && argc >= 5))
	{
		printf("ARGÜMAN SAYISI GEÇERSİZ\n");
		return (0);
	}
	if (!check_arg(argv))
		return (0);
	meta = get_meta(argv);
	meta.forks = malloc(sizeof(pthread_mutex_t) * meta.number_of_philosophers);
	philo = malloc(sizeof(s_philo) * meta.number_of_philosophers);
	printf("IMWORKING1\n");
	create_philo(&philo, meta);
	printf("IMWORKING2\n");
	set_forks_and_start_life_loop(&philo, meta);
	printf("IMWORKING3\n");
	if(control_philo(philo) == 1)
	{
		meta.stop_flag = 1;
		printf("HERKES YAŞIYOR VE DOYDU!!\n");
	}
	else
	{
		meta.stop_flag = 1;
		printf("ÖLÜ VAR \n");
	}

	i = 0;
	while (i < meta.number_of_philosophers)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	return (0);
}
