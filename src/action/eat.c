/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:14:35 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/18 11:16:49 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork->mutex);
	philo->left_fork->flag = 1;
	pthread_mutex_unlock(philo->left_fork->mutex);
	pthread_mutex_lock(philo->right_fork->mutex);
	philo->right_fork->flag = 1;
	pthread_mutex_unlock(philo->right_fork->mutex);
}

int	try_take_fork(t_mutex *fork)
{
	int	is_available;

	pthread_mutex_lock(fork->mutex);
	is_available = fork->flag;
	if (is_available)
		fork->flag = 0;
	pthread_mutex_unlock(fork->mutex);
	return (is_available);
}

void	set_forks_to_prev_state(int left_state, int right_state, t_philo *philo)
{
	if (left_state)
	{
		pthread_mutex_lock(philo->left_fork->mutex);
		philo->left_fork->flag = 1;
		pthread_mutex_unlock(philo->left_fork->mutex);
	}
	if (right_state)
	{
		pthread_mutex_lock(philo->right_fork->mutex);
		philo->right_fork->flag = 1;
		pthread_mutex_unlock(philo->right_fork->mutex);
	}
}

int	try_take_forks(t_philo *philo)
{
	const int has_take_left = try_take_fork(philo->left_fork);
	const int has_take_right = try_take_fork(philo->right_fork);

	if (has_take_left && has_take_right)
	{
		print_action("has taken a fork", philo);
		print_action("has taken a fork", philo);
	}
	else
		set_forks_to_prev_state(has_take_left, has_take_right, philo);
	return (has_take_left && has_take_right);
}

void	eat(t_philo *philo)
{
	print_action("is eating", philo);
	philo->last_eat = get_millisecond();
	ft_usleep(philo->time.time_to_eat, philo);
	release_forks(philo);
}
