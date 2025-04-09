/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_death_and_eat_count.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:10:36 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/09 17:22:13 by edarnand         ###   ########.fr       */
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
	i = 0;
	while (i < quantity_philo)
	{
		pthread_join(philos[i].th, NULL);
		i++;
	}
}

static int	get_stop_mut_value(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(philo->stop_mut->mutex);
	flag = philo->stop_mut->flag;
	pthread_mutex_unlock(philo->stop_mut->mutex);
	return (flag);
}

static int	death_of_philos(int quantity_philo, t_philo *philos)
{
	const pthread_mutex_t	*can_print = philos[0].can_print;
	const long				start_time = philos[0].time.start_time;
	int						i;
	int						death_id;

	i = 0;
	while (i < quantity_philo)
	{
		if (get_stop_mut_value(philos + i) == 1)
		{
			death_id = philos[i].id;
			stop_every_philos(quantity_philo, philos);
			pthread_mutex_lock((pthread_mutex_t *)can_print);
			printf("%ld %d died\n", get_millisecond() - start_time, death_id);
			pthread_mutex_unlock((pthread_mutex_t *)can_print);
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
			break ;
		}
		pthread_mutex_unlock(philos[i].eat_count->mutex);
		i++;
	}
	if (i != table.amount_philo)
		return (0);
	stop_every_philos(table.amount_philo, philos);
	return (1);
}

void	verif_death_and_eat_count(t_table table, t_philo *philos)
{
	while (1)
	{
		if (death_of_philos(table.amount_philo, philos))
			break ;
		if (table.each_philo_have_to_eat != -1
			&& philos_eat_enough(table, philos))
			break ;
	}
}
