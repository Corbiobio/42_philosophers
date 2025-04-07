/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:14:35 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/07 16:09:05 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	eat(t_philo *philo, int *f1_state, int *f2_state)
{
	print_action("is eating", philo);
	philo->last_eat = get_millisecond();
	ms_usleep_check_stop(philo->time.time_to_eat, philo);
	if (philo->state == ALIVE)
	{
		pthread_mutex_lock(philo->eat_count->mutex);
		philo->eat_count->flag++;
		pthread_mutex_unlock(philo->eat_count->mutex);
	}
		release_forks(philo);
	*f1_state = 0;
	*f2_state = 0;
}