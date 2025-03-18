/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:30:08 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/17 17:31:15 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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
		i++;
	}
	i = 0;
	long	time = get_millisecond();
	while (i < table.amount_philo)
	{
		philos[i].time.start_time = time;
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
