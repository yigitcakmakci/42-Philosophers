#include<sys/time.h>
#include<unistd.h>

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

unsigned long get_time_in_ms(void)
{
	struct timeval val;
	unsigned long res;
	gettimeofday(&val, NULL);

	res = (val.tv_sec * 1000);
	res += (val.tv_usec / 1000);
	return res;
}