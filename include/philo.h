/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:57:07 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/04 18:27:00 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef enum e_state
{
	ALIVE,
	STOP,
	DEAD
}	t_state;

typedef struct s_time
{
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long		start_time;
}	t_time;

typedef struct s_mutex
{
	int				flag;
	pthread_mutex_t	*mutex;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	long			last_eat;
	pthread_mutex_t	*can_print;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_mutex			*eat_count;
	t_mutex			*stop_mut;
	t_state			state;
	t_time			time;
}	t_philo;

typedef struct s_table
{
	int			amount_philo;
	int			each_philo_have_to_eat;
	t_time		time;
}	t_table;

//philo
void	*philo_routine(void *philo_pointer);

//action
//eat
void	eat(t_philo *philo);
int		try_take_fork(t_mutex *fork);//REMOVE
void	release_fork(t_mutex *fork);

//sleep
void	sleep_philo(t_philo *philo);

//init_and_clear_philo
t_philo	*init_philos(t_table table, t_mutex *forks, pthread_mutex_t *can_print);

//mutex
void	clear_mutex_arr(t_mutex *mutex_arr, int philo_quantity);
t_mutex	*init_mutex_arr(int philo_quantity);

//utils
long	get_millisecond(void);
void	print_action(char *action, t_philo *philo);
void	check_death(long curr_ms, t_philo *philo);
void	ms_usleep_deathcheck(long time, t_philo *philo);
void	ms_usleep_until_time(long time);

#endif
