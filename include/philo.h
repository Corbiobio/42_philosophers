/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:57:07 by edarnand          #+#    #+#             */
/*   Updated: 2025/03/17 15:05:15 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_time
{
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
} t_time;

typedef enum e_state
{
	DYING,
	EATING,
	SLEEPING,
	THINKING,
} t_state;

typedef struct s_mutex
{
	int				flag;
	pthread_mutex_t	*mutex;
} t_mutex;

typedef struct s_philo
{
	pthread_t	th;
	int			id;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	int			eat_count;
	long		last_eat;
	t_state		state;
	t_time		time;
} t_philo;

typedef struct s_table
{
	int			amount_philo;
	int			each_philo_have_to_eat;
	t_time		time;
} t_table;

//forks
t_mutex	*init_forks(int quantity);
int		get_fork_index(int max_forks, int id);
void	clear_forks(t_mutex *forks, int quantity);

//utils
long	get_millisecond(void);
void	print_action(char *action, t_philo *philo);

#endif
