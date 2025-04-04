/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:50:46 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/04 19:11:37 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	clear_mutex_arr(t_mutex *mutex_arr, int philo_quantity)
{
	int	i;

	i = 0;
	while (i < philo_quantity)
	{
		pthread_mutex_destroy(mutex_arr[i].mutex);
		free(mutex_arr[i].mutex);
		i++;
	}
	free(mutex_arr);
}

static t_mutex	*error_initing_arr(int index_error, t_mutex *arr)
{
	int	i;

	i = 0;
	while (i < index_error)
	{
		pthread_mutex_destroy(arr[i].mutex);
		free(arr[i].mutex);
		i++;
	}
	free(arr);
	exit(EXIT_FAILURE);
}

t_mutex	*init_mutex_arr(int philo_quantity)
{
	t_mutex	*arr;
	int		i;

	philo_quantity *= 3;
	i = 0;
	arr = malloc(sizeof(t_mutex) * philo_quantity);
	if (arr == NULL)
		exit(EXIT_FAILURE);
	while (i < philo_quantity)
	{
		if (i < philo_quantity / 3)
			arr[i].flag = 1;
		else
			arr[i].flag = 0;
		arr[i].mutex = malloc(sizeof(pthread_mutex_t));
		if (arr[i].mutex == NULL)
			break ;
		else
			pthread_mutex_init(arr[i].mutex, NULL);
		i++;
	}
	if (i < philo_quantity)
		error_initing_arr(i, arr);
	return (arr);
}
