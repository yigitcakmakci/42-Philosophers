/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:33:50 by ycakmakc          #+#    #+#             */
/*   Updated: 2026/01/15 15:08:37 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_metabolism	meta;
	t_philo			*philo;

	if (!check_arg(argc, argv))
		return (0);
	if (init_simulation(&philo, &meta, argv) != 0)
		return (1);
	if (control_philo(philo) == 1)
		change_stop_flag(&meta);
	else
		change_stop_flag(&meta);
	cleanup_mutexes(philo, &meta);
	free(meta.forks);
	free(philo);
	return (0);
}
