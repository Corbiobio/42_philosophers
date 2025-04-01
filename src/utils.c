/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:58:49 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/01 11:47:30 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

long	get_millisecond(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(char *action, t_philo *philo)
{
	pthread_mutex_lock(	philo->can_print);
	printf("%ld %d %s\n", get_millisecond() - philo->time.start_time, philo->id, action);
	pthread_mutex_unlock(philo->can_print);	
}


void	check_death(t_philo *philo)
{
	if(get_millisecond() - philo->last_eat > philo->time.time_to_die)
	{
		philo->is_dead = 1;
	}
}

void	ms_usleep_deathcheck(long time, t_philo *philo)
{
	const long	start = get_millisecond();

	while ((get_millisecond() - start) < time && !philo->is_dead)
	{
		usleep(500);
		check_death(philo);
	}
}

