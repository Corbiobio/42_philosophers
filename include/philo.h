/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:57:07 by edarnand          #+#    #+#             */
/*   Updated: 2025/04/01 14:02:04 by edarnand         ###   ########.fr       */
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
	long		start_time;
} t_time;

typedef struct s_mutex
{
	int				flag;
	pthread_mutex_t	*mutex;
} t_mutex;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	pthread_mutex_t	*can_print;
	int				eat_count;
	long			last_eat;
	int				is_dead;
	t_time			time;
} t_philo;

typedef struct s_table
{
	int			amount_philo;
	int			each_philo_have_to_eat;
	t_time		time;
} t_table;

//philo
void	*philo_routine(void *philo_pointer);

//action eat
void	eat(t_philo *philo);
int		try_take_forks(t_philo *philo);

//init_and_clear_philo
t_philo	*init_philos(t_table table, t_mutex *forks, pthread_mutex_t *can_print);

//forks
t_mutex	*init_forks(int quantity);
int		get_fork_index(int max_forks, int id);
void	clear_forks(t_mutex *forks, int quantity);

//utils
long	get_millisecond(void);
void	print_action(char *action, t_philo *philo);
void	check_death(t_philo *philo);
void	ms_usleep_deathcheck(long time, t_philo *philo);
void	ms_usleep_until_time(long time);

#endif
