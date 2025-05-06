/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/06 11:51:46 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static void	philo_life(t_philo *philo)
{
	int		has_take_left;
	int		has_take_right;

	has_take_left = 0;
	has_take_right = 0;
	while (philo->state == ALIVE)
	{
		if (!has_take_left)
			has_take_left = try_take_fork(philo->left_fork, philo);
		if (!has_take_right)
			has_take_right = try_take_fork(philo->right_fork, philo);
		if (has_take_left && has_take_right)
		{
			eat(philo, &has_take_left, &has_take_right);
			if (philo->state == ALIVE)
				sleep_philo(philo);
		}
		else
		{
			check_death(get_millisecond(), philo);
			usleep(500);
		}
	}
}

void	*philo_routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(philo->stop_mut->mutex);
	philo->stop_mut->flag = 0;
	philo->state = ALIVE;
	pthread_mutex_unlock(philo->stop_mut->mutex);
	while (get_millisecond() < philo->time.start_time)
		usleep(500);
	print_action("is thinking", philo);
	if (philo->id % 2 == 0 && philo->time.time_to_eat < philo->time.time_to_die)
		ms_usleep_check_stop(philo->time.time_to_eat * 500, philo);
	philo_life(philo);
	return (NULL);
}
