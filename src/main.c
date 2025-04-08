/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:06:16 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/08 18:07:39 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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
	table.amount_philo = 200;
	table.each_philo_have_to_eat = -1;
	table.time.time_to_eat = 300;
	table.time.time_to_sleep = 300;
	table.time.time_to_die = 610;
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