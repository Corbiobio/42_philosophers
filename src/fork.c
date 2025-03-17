/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:46 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/17 11:48:43 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	get_fork_index(int max_forks, int id)
{
	if (id < 0)
		return (max_forks - 1);
	else
		return (id);
}

void	clear_forks(t_mutex *forks, int quantity)
{
	int	i;

	i = 0;
	while (i < quantity)
	{
		pthread_mutex_destroy(forks[i].mutex);
		free(forks[i].mutex);
		i++;
	}
	free(forks);
}

static t_mutex	*forks_error(int index_error, t_mutex *forks)
{

	while (index_error >= 0)
	{
		pthread_mutex_destroy(forks[index_error].mutex);
		free(forks[index_error].mutex);
		index_error--;
	}
	free(forks);
	return (NULL);
}

t_mutex	*init_forks(int quantity)
{
	t_mutex	*forks;
	int		i;
	int		error;

	forks = malloc(sizeof(t_mutex) * quantity);
	if (forks == NULL)
		return (NULL);
	i = 0;
	error = 0;
	while (i < quantity && error == 0)
	{
		forks[i].flag = 1;
		forks[i].mutex = malloc(sizeof(pthread_mutex_t) * 1);
		if (forks[i].mutex == NULL)
			error = 1;
		else
			pthread_mutex_init(forks[i].mutex, NULL);
		if (forks[i].mutex == NULL)
			error = 1;
		i++;
	}
	if (error == 1)
		return (forks_error(i - 1, forks));
	return (forks);
}
