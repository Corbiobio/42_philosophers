/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/04 18:12:52 by edarnand         ###   ########.fr       */
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
	int		has_take_left;
	int		has_take_right;

	philo = (t_philo *)philo_pointer;
	has_take_left = 0;
	has_take_right = 0;
	ms_usleep_until_time(philo->time.start_time);
	print_action("start", philo);
	if (philo->id % 2 == 0)
		usleep(philo->time.time_to_eat * 500);


 
	while (philo->state == ALIVE)
	{
		if (!has_take_left)
			has_take_left = try_take_fork(philo->left_fork);
		if (!has_take_right)
			has_take_right = try_take_fork(philo->right_fork);
		if (has_take_left && has_take_right)
		{
			eat(philo);
			release_fork(philo->left_fork);
			release_fork(philo->right_fork);
			has_take_left = 0;
			has_take_right = 0;
			if (philo->state == ALIVE)
				sleep_philo(philo);
		}
		else
		{
			check_death(get_millisecond(), philo);
			usleep(100);
		}
	}
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(philo->can_print);
		printf("%ld %d %s\n",
			get_millisecond() - philo->time.start_time, philo->id, "died");
		pthread_mutex_unlock(philo->can_print);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table			table;
	t_mutex			*mutex_arr;
	t_philo			*philos;
	pthread_mutex_t	can_print;

	//TODO parsing
	//TODO if (argc < || argc > || table->philo_num <= 0 || table->philo_num > 200 || table->death_time < 0 || table->eat_time < 0 || table->sleep_time < 0)
	table.amount_philo = 5;
	table.each_philo_have_to_eat = -1;
	table.time.time_to_eat = 300;
	table.time.time_to_sleep = 300;
	table.time.time_to_die = 905;
	mutex_arr = init_mutex_arr(table.amount_philo);
	pthread_mutex_init(&can_print, NULL);
	philos = init_philos(table, mutex_arr, &can_print);
	//verif death and eat count
	while (1);
	free(philos);
	pthread_mutex_destroy(&can_print);
	clear_mutex_arr(mutex_arr, table.amount_philo);
	(void)ac;
	(void)av;
	return (0);
}
