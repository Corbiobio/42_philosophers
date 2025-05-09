/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:30:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/06 11:54:04 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

static t_philo	*error_initing_philos(t_table table, t_mutex *mutex_arr,
	pthread_mutex_t *can_print)
{
	clear_mutex_arr(mutex_arr, table.amount_philo);
	pthread_mutex_destroy(can_print);
	return (NULL);
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
		if (i - 1 < 0)
			philos[i].left_fork = mutex_arr + (table.amount_philo - 1);
		else
			philos[i].left_fork = mutex_arr + (i - 1);
		philos[i].eat_count = mutex_arr + i + table.amount_philo;
		philos[i].eat_count->flag = 0;
		philos[i].stop_mut = mutex_arr + i + table.amount_philo
			+ table.amount_philo;
		philos[i].state = DEAD;
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
		return (error_initing_philos(table, mutex_arr, can_print));
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
	while (get_millisecond() < table.time.start_time)
		usleep(500);
	return (philos);
}
