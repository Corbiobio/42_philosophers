/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:30:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/21 17:32:31 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_philo	*init_philos(t_table table, t_mutex *forks, t_mutex *mut)
{
	int		i;
	t_philo *philos;
	long	time;

	philos = malloc(sizeof(t_philo) * table.amount_philo);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < table.amount_philo)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].right_fork = forks + i;
		philos[i].left_fork = forks + get_fork_index(table.amount_philo, i - 1);
		philos[i].is_dead = 0;
		philos[i].time = table.time;
		philos[i].someone_died = mut;
		i++;
	}
	i = 0;
	time = get_millisecond();
	while (i < table.amount_philo)
	{
		philos[i].time.start_time = time;
		i++;
	}
	i = 0;
	while (i < table.amount_philo)
	{
		pthread_create(&philos[i].th, NULL, &philo_routine, philos + i);
		i++;
	}
	i = 0;
	while (i < table.amount_philo)
	{
		pthread_detach(philos[i].th);
		i++;
	}
	return (philos);
}

void	verif_death_or_eat_count_philos(t_philo *philos, t_table table)
{
	int	i;
	int	is_end;
	int	total_eat;

	is_end = 0;
	while (!is_end)
	{
		usleep(table.time.time_to_die);
		i = 0;
		total_eat = 0;
		while (i < table.amount_philo)
		{
			//printf("%d eat %d\n", philos[i].id, philos[i].eat_count);
			if (philos[i].is_dead)
			{
				is_end = 1;
				break ;
			}
			if (philos[i].eat_count >= table.each_philo_have_to_eat)
				total_eat += table.each_philo_have_to_eat;
			i++;
		}
		//printf("%d\n", table.amount_philo * table.each_philo_have_to_eat);
		if (table.each_philo_have_to_eat >= 1 && total_eat == table.amount_philo * table.each_philo_have_to_eat)
			break ;
	}
}
