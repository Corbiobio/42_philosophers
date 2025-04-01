/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:30:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/01 14:09:25 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_philo	*init_philos(t_table table, t_mutex *forks, pthread_mutex_t *can_print)
{
	int		i;
	t_philo *philos;

	
	philos = malloc(sizeof(t_philo) * table.amount_philo);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < table.amount_philo)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].right_fork = forks + i;
		philos[i].left_fork = forks + get_fork_index(table.amount_philo, i - 1);
		philos[i].state = ALIVE;
		philos[i].can_print = can_print;
		i++;
	}
	i = 0;
	table.time.start_time = get_millisecond() + 50;
	while (i < table.amount_philo)
	{
		philos[i].time = table.time;
		pthread_create(&philos[i].th, NULL, &philo_routine, philos + i);
		i++;
	}
	i = 0;
	while (i < table.amount_philo)
	{
		pthread_detach(philos[i].th);
		i++;
	}
	return (philos);
}
