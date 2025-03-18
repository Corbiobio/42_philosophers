/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/18 11:18:14 by edarnand         ###   ########.fr       */
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
	ft_usleep(philo->time.time_to_sleep, philo);
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
		if (philo->state == SLEEPING)
			sleep_philo(philo);
	}
	print_action("died", philo);
	return (&philo->id);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_time	time;
	t_mutex *forks;
	t_philo *philos;

	//TODO parsing
	//TODO if (table->philo_num <= 0 || table->philo_num > 200 || table->death_time < 0 || table->eat_time < 0 || table->sleep_time < 0)
	table.amount_philo = 6;
	table.each_philo_have_to_eat = 0;
	time.time_to_eat = 3000;
	time.time_to_sleep = 2000;
	time.time_to_die = 6000;
	table.time = time;

	forks = init_forks(table.amount_philo);
	if (forks == NULL)
		return (EXIT_FAILURE);
	philos = init_philos(table, forks);
	if (forks == NULL)
		return (EXIT_FAILURE);
	wait_and_clear_philos(philos, table.amount_philo);
	clear_forks(forks, table.amount_philo);
	(void)ac;
	(void)av;
	return (0);
}
