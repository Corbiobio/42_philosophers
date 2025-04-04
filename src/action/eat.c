/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:14:35 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/04 18:39:00 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	print_eat(t_philo *philo)
{
	long	ms;

	if (philo->state == ALIVE)
	{
		ms = get_millisecond() - philo->time.start_time;
		pthread_mutex_lock(philo->can_print);
		printf("%ld %d %s\n", ms, philo->id, "has taken a fork");
		printf("%ld %d %s\n", ms, philo->id, "has taken a fork");
		printf("%ld %d %s\n", ms, philo->id, "is eating");
		pthread_mutex_unlock(philo->can_print);
	}
}

void	eat(t_philo *philo, int *f1_state, int *f2_state)
{
	print_eat(philo);
	pthread_mutex_lock(philo->eat_count->mutex);
	philo->eat_count->flag++;
	pthread_mutex_unlock(philo->eat_count->mutex);
	philo->last_eat = get_millisecond();
	ms_usleep_deathcheck(philo->time.time_to_eat, philo);
	release_forks(philo);
	*f1_state = 0;
	*f2_state = 0;
}