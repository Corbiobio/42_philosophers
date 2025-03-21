/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:58:49 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/21 12:12:53 by edarnand         ###   ########.fr       */
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
	printf("%ld %d %s\n", get_millisecond() - philo->time.start_time, philo->id, action);
}


void	check_death(t_philo *philo)
{
	if(get_millisecond() - philo->last_eat > philo->time.time_to_die)
		philo->state = DYING;
}

void	ms_usleep_deathcheck(long time, t_philo *philo)
{
	const long	start = get_millisecond();

	while ((get_millisecond() - start) < time && philo->state != DYING)
	{
		usleep(100);
		check_death(philo);
	}
}

