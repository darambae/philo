/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:26:16 by dabae             #+#    #+#             */
/*   Updated: 2024/05/06 17:28:59 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include <stdbool.h>

enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	FULL,
	DEAD
};

enum e_mutex
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
};

typedef struct s_data
{
	int				num_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_must_eat;
	uint64_t		simul_start;

	int				num_full;
	pthread_mutex_t	full_lock;
	bool			stop;
	pthread_mutex_t	stop_lock;

	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	exit_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_t		*tids;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				num_eat;
	bool			is_eating;
	bool			is_full;
	uint64_t		start_time;
	pthread_mutex_t	start_time_lock;
	pthread_mutex_t	num_eat_lock;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

int			is_digit(char **args);
int			is_positive(char **str);
long		ft_atoi(char *str);
void		ft_usleep(uint64_t elapsed);
void		ft_exit(t_data *data, int err, char *msg);
uint64_t	get_time(void);
void		mutex_handler(t_data *data, pthread_mutex_t *mutex, int type);
int			init_philo(t_data *data);
void		init_data(t_data *data, char **args);
void		set_num_eat(t_philo *philo);
void		set_stop(t_data *data);
void		set_start_time(t_philo *philo, uint64_t time);
void		set_eating(t_philo *philo, bool setting);
void		print(t_philo *philo, char *str);
int			check_death(t_philo *philo);
int			check_full(t_philo *philo);
int			monitoring_num_eat(t_philo *philo);
void		check_to_stop(t_data *data);
int			time_to_stop(t_philo *philo);
void		join_threads(t_data *data);
void		life_cycle(t_data *data);
int			take_forks(t_philo *philo);
int			unlock_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_phase(t_philo *philo);
void		think(t_philo *philo);

#endif