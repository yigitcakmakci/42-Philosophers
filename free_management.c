/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:22:15 by ycakmakc          #+#    #+#             */
/*   Updated: 2025/12/25 14:41:03 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>//DİKKAT

void	free_all(t_philo **philo)
{
	//int i = 0;

	free(philo[0]);
	/*while (philo[i])
	{
		printf("philo[%d] freeleniyor...\n", i);
		//free(philo[i]->right_fork);
		free(philo[i]);
		i++;
	}*/
}