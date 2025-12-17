/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:06:40 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/17 22:09:35 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
