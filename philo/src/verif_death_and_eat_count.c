/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_death_and_eat_count.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:10:36 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/09 15:43:39 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	stop_every_philos(int quantity_philo, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < quantity_philo)
	{
		pthread_mutex_lock(philos[i].stop_mut->mutex);
		philos[i].stop_mut->flag = 1;
		pthread_mutex_unlock(philos[i].stop_mut->mutex);
		i++;
	}
}

int	death_of_philos(int quantity_philo, t_philo *philos)
{
	int	i;
	int	is_dead;

	i = 0;
	is_dead = 0;
	while (i < quantity_philo)
	{
		pthread_mutex_lock(philos[i].stop_mut->mutex);
		is_dead = philos[i].stop_mut->flag;
		pthread_mutex_unlock(philos[i].stop_mut->mutex);
		if (is_dead)
		{
			stop_every_philos(quantity_philo, philos);
			pthread_mutex_lock(philos[i].can_print);
			printf("%ld %d died\n",
				get_millisecond() - philos[i].time.start_time, philos[i].id);
			pthread_mutex_unlock(philos[i].can_print);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philos_eat_enough(t_table table, t_philo *philos)
{
	int	total_eat;
	int	i;

	i = 0;
	total_eat = 0;
	while (i < table.amount_philo)
	{
		pthread_mutex_lock(philos[i].eat_count->mutex);
		if (philos[i].eat_count->flag < table.each_philo_have_to_eat)
		{
			pthread_mutex_unlock(philos[i].eat_count->mutex);
			stop_every_philos(table.amount_philo, philos);
			break ;
		}
		pthread_mutex_unlock(philos[i].eat_count->mutex);
		i++;
	}
	return (i == table.amount_philo);
}

void	verif_death_and_eat_count(t_table table, t_philo *philos)
{
	const int	quantity_philo = table.amount_philo;

	while (1)
	{
		if (death_of_philos(quantity_philo, philos))
			break ;
		if (table.each_philo_have_to_eat != -1
			&& philos_eat_enough(table, philos))
			break ;
	}
}
