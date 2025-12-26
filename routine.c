#include "philo.h"
#include "unistd.h"

int		check_stop(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->metabolism->dead_lock);
	ret = philo->metabolism->stop_flag;
	pthread_mutex_unlock(&philo->metabolism->dead_lock);
	return (ret);
}

void	*life_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->current.id % 2 == 0)
		usleep(1000);
	while (check_stop(philo) == 0)
	{
		if (philo->current.id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			safe_print(philo, 1);
			pthread_mutex_lock(philo->left_fork);
			safe_print(philo, 1);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			safe_print(philo, 1);
			pthread_mutex_lock(philo->right_fork);
			safe_print(philo, 1);
		}
		safe_print(philo, 2);
		pthread_mutex_lock(&philo->metabolism->dead_lock);
		philo->current.last_eat = get_time_in_ms();
		pthread_mutex_unlock(&philo->metabolism->dead_lock);
		usleep(philo->metabolism->time_to_eat * 1000);
		pthread_mutex_lock(&philo->metabolism->dead_lock);
		philo->current.eat_count++;
		pthread_mutex_unlock(&philo->metabolism->dead_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		safe_print(philo, 3);
		usleep(philo->metabolism->time_to_sleep * 1000);
		safe_print(philo, 4);
	}
	return ((void *)0);
}