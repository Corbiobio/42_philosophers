/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/21 13:03:42 by edarnand         ###   ########.fr       */
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

void	sleep_philo(t_philo *philo)
{
	print_action("is sleeping", philo);
	ms_usleep_deathcheck(philo->time.time_to_sleep, philo);
	if (philo->state != DYING)
	{
		philo->state = THINKING;
		print_action("is thinking", philo);
	}
}

void	*philo_routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->last_eat = philo->time.start_time;
	print_action("is thinking", philo);
	while (philo->state != DYING)
	{
		check_death(philo);
		if (philo->state == THINKING && try_take_forks(philo) == 1)
		{
			eat(philo);
			if (philo->state != DYING)
				philo->state = SLEEPING;
		}
		else
			usleep(1);
		if (philo->state == SLEEPING)
			sleep_philo(philo);
	}
	print_action("died", philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_time	time;
	t_mutex *forks;
	t_philo *philos;

	//TODO parsing
	//TODO if (argc < || argc > || table->philo_num <= 0 || table->philo_num > 200 || table->death_time < 0 || table->eat_time < 0 || table->sleep_time < 0)
	table.amount_philo = 6;
	table.each_philo_have_to_eat = -1;
	time.time_to_eat = 100;
	time.time_to_sleep = 100;
	time.time_to_die = 210;
	table.time = time;

	forks = init_forks(table.amount_philo);
	if (forks == NULL)
		return (EXIT_FAILURE);
	philos = init_philos(table, forks);
	if (philos == NULL)
	{
		clear_forks(forks, table.amount_philo);
		return (EXIT_FAILURE);
	}
	//verif_death_or_eat_count_philos(philos, table);
	while (1);
	free(philos);
	clear_forks(forks, table.amount_philo);
	(void)ac;
	(void)av;
	return (0);
}
