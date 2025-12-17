#include <stdio.h>
int	is_number(char *arg)
{
	int	i;

	if (arg == ((void*)0))
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
	return(1);
}


int	check_arg(char **argv)
{
	int i = 1;
	while (argv[i] && i < 5)
	{
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}