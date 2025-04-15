/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:06:16 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/15 09:33:18 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	parsing(int ac, char **av, t_table *table)
{
	int	error;

	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	error = ft_atol_protected(av[1], &table->amount_philo);
	error += ft_atol_protected(av[2], &table->time.time_to_die);
	error += ft_atol_protected(av[3], &table->time.time_to_eat);
	error += ft_atol_protected(av[4], &table->time.time_to_sleep);
	table->each_philo_have_to_eat = -1;
	if (ac == 6)
		error += ft_atol_protected(av[5], &table->each_philo_have_to_eat);
	if (error != ac - 1 || table->amount_philo < 1 || table->time.time_to_die
		< 0 || table->time.time_to_eat < 0 || table->time.time_to_sleep < 0
		|| (ac == 6 && table->each_philo_have_to_eat < 1))
	{
		printf("Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_table			table;
	t_mutex			*mutex_arr;
	t_philo			*philos;
	pthread_mutex_t	can_print;

	if (parsing(ac, av, &table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mutex_arr = init_mutex_arr(table.amount_philo);
	if (mutex_arr == NULL)
		return (EXIT_FAILURE);
	pthread_mutex_init(&can_print, NULL);
	philos = init_philos(table, mutex_arr, &can_print);
	if (philos == NULL)
		return (EXIT_FAILURE);
	verif_death_and_eat_count(table, philos);
	free(philos);
	pthread_mutex_destroy(&can_print);
	clear_mutex_arr(mutex_arr, table.amount_philo);
	return (EXIT_SUCCESS);
}
