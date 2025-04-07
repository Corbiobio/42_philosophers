/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:31:15 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/07 16:09:54 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	get_fork_index(int max_forks, int id)
{
	if (id < 0)
		return (max_forks - 1);
	else
		return (id);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork->mutex);
	philo->left_fork->flag = 1;
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	philo->right_fork->flag = 1;
	pthread_mutex_unlock(philo->right_fork->mutex);
}

int	try_take_fork(t_mutex *fork, t_philo *philo)
{
	int	is_available;

	pthread_mutex_lock(fork->mutex);
	is_available = fork->flag;
	if (is_available)
		fork->flag = 0;
	pthread_mutex_unlock(fork->mutex);
	if (is_available)
		print_action("has taken a fork", philo);
	return (is_available);
}
