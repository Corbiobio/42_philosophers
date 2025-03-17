/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:56:50 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/17 17:09:40 by edarnand         ###   ########.fr       */
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

int	try_take_forks(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	state = philo->left_fork->flag && philo->right_fork->flag;

	if (state)
	{
		print_action("has taken a fork", philo);
		print_action("has taken a fork", philo);
		philo->right_fork->flag = 0;
		philo->left_fork->flag = 0;
	}
	pthread_mutex_unlock(philo->right_fork->mutex);
	pthread_mutex_unlock(philo->left_fork->mutex);

	return (state);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork->mutex);
	philo->left_fork->flag = 1;
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	philo->right_fork->flag = 1;
	pthread_mutex_unlock(philo->right_fork->mutex);
}

void	check_death(t_philo *philo)
{
	if(get_millisecond() - philo->last_eat > philo->time.time_to_die)
		philo->state = DYING;
}

void	ft_usleep(long time, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < time * 2 && philo->state != DYING)
	{
		usleep(500);
		check_death(philo);
		i++;
	}
}

void	take_fork_and_eat(t_philo *philo)
{
	print_action("is eating", philo);
	philo->last_eat = get_millisecond();
	ft_usleep(philo->time.time_to_eat, philo);
	release_fork(philo);
}

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
	philo->last_eat = get_millisecond();
	philo->time.start_time = philo->last_eat;
	print_action("is thinking", philo);
	while (philo->state != DYING)
	{
		if (philo->state == THINKING && try_take_forks(philo) == 1)
		{
			take_fork_and_eat(philo);
			if (philo->state != DYING)
				philo->state = SLEEPING;
		}
		if (philo->state == SLEEPING)
			sleep_philo(philo);
	}
	print_action("died", philo);
	return (&philo->id);
}

t_philo	*init_philos(t_table table, t_mutex *forks)
{
	int		i;
	t_philo *philos;
	
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
		philos[i].state = THINKING;
		philos[i].time = table.time;
		pthread_create(&philos[i].th, NULL, &philo_routine, philos + i);
		i++;
	}
	return (philos);
}

void	wait_and_clear_philos(t_philo *philos, int quantity)
{
	int	i;
	int	*id;

	i = 0;
	while (i < quantity)
	{
		pthread_join(philos[i].th, (void **)&id);
		i++;
	}
	free(philos);
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
	time.time_to_die = 5500;
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
