/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/01 14:13:32 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

void	*philo_routine(void *philo_pointer)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_pointer;
	philo->last_eat = philo->time.start_time;
	ms_usleep_until_time(philo->time.start_time);
	print_action("start", philo);
	
	if (philo->id % 2 == 0)
		usleep(philo->time.time_to_eat * 500);
	while (philo->state == ALIVE)
	{
		if (try_take_forks(philo) == 1)
		{
			eat(philo);
			if (philo->state == ALIVE)
				sleep_philo(philo);
		}
		else
		{
			check_death(philo);
			usleep(1);
		}
	}
	if (philo->state == DEAD)
		print_action("died", philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_mutex *forks;
	t_philo *philos;
	pthread_mutex_t	can_print;

	//TODO parsing
	//TODO if (argc < || argc > || table->philo_num <= 0 || table->philo_num > 200 || table->death_time < 0 || table->eat_time < 0 || table->sleep_time < 0)
	table.amount_philo = 200;
	table.each_philo_have_to_eat = -1;
	table.time.time_to_eat = 200;
	table.time.time_to_sleep = 200;
	table.time.time_to_die = 600;
	pthread_mutex_init(&can_print, NULL);
	forks = init_forks(table.amount_philo);
	if (forks == NULL)
		return (EXIT_FAILURE);

	philos = init_philos(table, forks, &can_print);

	if (philos != NULL)
	{
		//verif_death_or_eat_count_philos
		while (1);
		free(philos);
	}
	
	pthread_mutex_destroy(&can_print);
	clear_forks(forks, table.amount_philo);
	(void)ac;
	(void)av;
	return (0);
}
