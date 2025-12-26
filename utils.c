#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

unsigned long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void safe_print(t_philo *philo, int status)
{
    unsigned long time;

    pthread_mutex_lock(&philo->metabolism->print_mutex);
    pthread_mutex_lock(&philo->metabolism->dead_lock);
    if (philo->metabolism->stop_flag == 1)
    {
        pthread_mutex_unlock(&philo->metabolism->dead_lock);
        pthread_mutex_unlock(&philo->metabolism->print_mutex);
        return;
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
