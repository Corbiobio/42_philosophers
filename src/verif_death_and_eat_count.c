/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_death_and_eat_count.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:10:36 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/07 13:17:58 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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
			return (1);
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
	return (i == table.amount_philo);
}

void	verif_death_and_eat_count(t_table table, t_philo *philos)
{
	const int	quantity_philo = table.amount_philo;
	int	stop;

	stop = 0;
	while (!stop)
	{
		if (death_of_philos(quantity_philo, philos))
			stop = 1;
		else if (table.each_philo_have_to_eat != -1 && philos_eat_enough(table, philos))
			stop = 1;
		else
			usleep(500);
	}
	stop_every_philos(quantity_philo, philos);
}
