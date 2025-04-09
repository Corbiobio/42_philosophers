/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:06:16 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/09 13:33:24 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

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

static void	parsing(int ac, char **av, t_table *table)
{
	int	error;

	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	error = ft_atol_protected(av[1], &table->amount_philo);
	error += ft_atol_protected(av[2], &table->time.time_to_die);
	error += ft_atol_protected(av[3], &table->time.time_to_eat);
	error += ft_atol_protected(av[4], &table->time.time_to_sleep);
	if (ac == 6)
		error += ft_atol_protected(av[5], &table->each_philo_have_to_eat);
	if (ac == 5 || table->each_philo_have_to_eat < 1)
		table->each_philo_have_to_eat = -1;
	if (error != ac - 1 || table->amount_philo < 1 || table->time.time_to_die
		< 0 || table->time.time_to_eat < 0 || table->time.time_to_sleep < 0)
	{
		printf("Invalid arguments\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	t_table			table;
	t_mutex			*mutex_arr;
	t_philo			*philos;
	pthread_mutex_t	can_print;

	parsing(ac, av, &table);
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
