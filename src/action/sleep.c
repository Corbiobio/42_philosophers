/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:13:38 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/01 15:17:40 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_philo *philo)
{
	print_action("is sleeping", philo);
	ms_usleep_deathcheck(philo->time.time_to_sleep, philo);
	print_action("is thinking", philo);
}
