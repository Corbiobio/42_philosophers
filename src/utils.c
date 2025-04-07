/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:58:49 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/07 17:39:20 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
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
	if (philo->state == ALIVE)
	{
		pthread_mutex_lock(philo->can_print);
		printf("%ld %d %s\n",
			get_millisecond() - philo->time.start_time, philo->id, action);
		pthread_mutex_unlock(philo->can_print);
	}
}

static int	check_death(long curr_ms, t_philo *philo)
{
	if (curr_ms - philo->last_eat > philo->time.time_to_die)
	{
		pthread_mutex_lock(philo->stop_mut->mutex);
		philo->stop_mut->flag = 1;
		pthread_mutex_unlock(philo->stop_mut->mutex);
		pthread_mutex_lock(philo->can_print);
		printf("%ld %d %s\n",
			get_millisecond() - philo->time.start_time, philo->id, "died");
		pthread_mutex_unlock(philo->can_print);
		philo->state = DEAD;
		return (0);
	}
	return (1);
}

void	check_stop(long curr_ms, t_philo *philo)
{
	const int	is_alive = check_death(curr_ms, philo);
	
	if (is_alive)
	{
		pthread_mutex_lock(philo->stop_mut->mutex);
		if (philo->stop_mut->flag == 1 && philo->state == ALIVE)
			philo->state = STOP;
		pthread_mutex_unlock(philo->stop_mut->mutex);
	}
}

void	ms_usleep_check_stop(long ms_to_wait, t_philo *philo)
{
	const long	start = get_millisecond();
	long		curr_ms;

	curr_ms = start;
	while (curr_ms - start < ms_to_wait && philo->state == ALIVE)
	{
		usleep(500);
		check_stop(curr_ms, philo);
		curr_ms = get_millisecond();
	}
}

void	ms_usleep_until_time(long time)
{
	while (get_millisecond() < time)
		usleep(500);
}
