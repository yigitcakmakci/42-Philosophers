/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:04:38 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 15:09:39 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	is_number(char *arg)
{
	int	i;

	if (arg == NULL)
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
