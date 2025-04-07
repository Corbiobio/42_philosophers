/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:30:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/07 16:53:22 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	error_initing_philos(t_table table, t_mutex *mutex_arr,
	pthread_mutex_t *can_print)
{
	clear_mutex_arr(mutex_arr, table.amount_philo);
	pthread_mutex_destroy(can_print);
	exit(EXIT_FAILURE);
}

static void	init_basic_value(t_table table, t_mutex *mutex_arr,
	pthread_mutex_t *can_print, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table.amount_philo)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = mutex_arr + i;
		philos[i].left_fork = mutex_arr
			+ get_fork_index(table.amount_philo, i - 1);
		philos[i].eat_count = mutex_arr + i + table.amount_philo;
		philos[i].stop_mut = mutex_arr + i + table.amount_philo
			+ table.amount_philo;
		philos[i].state = ALIVE;
		philos[i].can_print = can_print;
		i++;
	}
}

t_philo	*init_philos(t_table table, t_mutex *mutex_arr,
	pthread_mutex_t *can_print)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * table.amount_philo);
	if (philos == NULL)
		error_initing_philos(table, mutex_arr, can_print);
	init_basic_value(table, mutex_arr, can_print, philos);
	i = 0;
	table.time.start_time = get_millisecond() + 100;
	while (i < table.amount_philo)
	{
		philos[i].time = table.time;
		philos[i].last_eat = table.time.start_time;
		pthread_create(&philos[i].th, NULL, &philo_routine, philos + i);
		i++;
	}
	return (philos);
}
