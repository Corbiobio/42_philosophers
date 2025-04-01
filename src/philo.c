/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/01 10:25:11 by edarnand         ###   ########.fr       */
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
	if (!philo->is_dead)
		print_action("is thinking", philo);
}

int	is_someone_died(t_mutex *someone_died)
{
	int	someone_death;

	pthread_mutex_lock(someone_died->mutex);
	someone_death = someone_died->flag;
	pthread_mutex_unlock(someone_died->mutex);
	return (someone_death);
}

void	*philo_routine(void *philo_pointer)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_pointer;

	pthread_mutex_lock(	philo->can_print);
	printf("%ld %d start\n", get_millisecond() - philo->time.start_time, philo->id);
	pthread_mutex_unlock(philo->can_print);

















	//print_action("is start", philo);
	//if (philo->id % 2 == 0)
	//	usleep(philo->time.time_to_eat / 2 * 1000);
	//while (!philo->is_dead)
	//{
	//	if (try_take_forks(philo) == 1)
	//	{
	//		eat(philo);
	//		if (!philo->is_dead)
	//			sleep_philo(philo);
	//	}
	//	else
	//		usleep(1);
	//	check_death(philo);
	//if (is_someone_died(philo->someone_died))
	//	break ;
	//}
	//if (philo->is_dead)
	//	print_action("died", philo);
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
	table.time.time_to_die = 500;
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
