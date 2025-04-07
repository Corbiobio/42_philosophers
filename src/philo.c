/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/07 16:54:19 by edarnand         ###   ########.fr       */
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
			check_stop(get_millisecond(), philo);
			usleep(100);
		}
	}
}

void	*philo_routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	ms_usleep_until_time(philo->time.start_time);
	print_action("start", philo);
	if (philo->id % 2 == 0)
		usleep(philo->time.time_to_eat * 500);
	philo_life(philo);
	return (NULL);
}

static void	join_every_philos(t_table table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table.amount_philo)
	{
		pthread_join(philos[i].th, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table			table;
	t_mutex			*mutex_arr;
	t_philo			*philos;
	pthread_mutex_t	can_print;

	//TODO PUT IT IN A FOLDER PHILO/
	//TODO parsing
	//TODO if (argc < || argc > || table->philo_num <= 0 || table->philo_num > 200 || table->death_time < 0 || table->eat_time < 0 || table->sleep_time < 0)
	table.amount_philo = 5;
	table.each_philo_have_to_eat = 5;
	table.time.time_to_eat = 300;
	table.time.time_to_sleep = 300;
	table.time.time_to_die = 910;
	mutex_arr = init_mutex_arr(table.amount_philo);
	pthread_mutex_init(&can_print, NULL);
	philos = init_philos(table, mutex_arr, &can_print);
	verif_death_and_eat_count(table, philos);
	join_every_philos(table, philos);
	free(philos);
	pthread_mutex_destroy(&can_print);
	clear_mutex_arr(mutex_arr, table.amount_philo);
	(void)ac;
	(void)av;
	return (0);
}
