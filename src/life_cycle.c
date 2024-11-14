/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:25:19 by dabae             #+#    #+#             */
/*   Updated: 2024/05/13 09:49:52 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	eat_phase(t_philo *philo)
{
	print(philo, "is eating");
	change_state(philo, EAT);
	ft_usleep(philo->param->time_to_eat);
	put_down_forks(philo);
	pthread_mutex_lock(&philo->lock);
	if (philo->num_eat == philo->param->num_must_eat)
	{
		philo->state = FULL;
		pthread_mutex_lock(&philo->param->lock);
		philo->param->num_full++;
		pthread_mutex_unlock(&philo->param->lock);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

static void	sleep_phase(t_philo *philo)
{
	change_state(philo, SLEEP);
	print(philo, "is sleeping");
	ft_usleep(philo->param->time_to_sleep);
}

static int	unlock_forks(t_philo *philo)
{
	if (check_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	*life_start(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	if (pthread_create(&phi->thread, NULL, &anyone_dead, phi) != 0)
		return ((void *)1);
	while (check_stop(phi) == 0)
	{
		if (check_stop(phi))
			break ;
		take_forks(philo);
		if (unlock_forks(phi))
			break ;
		eat_phase(phi);
		if (check_stop(phi))
			break ;
		sleep_phase(phi);
		if (check_stop(phi))
			break ;
		print(philo, "is thinking");
	}
	if (pthread_join(phi->thread, NULL) != 0)
		return ((void *)1);
	return ((void *)0);
}

int	life_cycle(t_param *param)
{
	pthread_t	thread;
	int			i;

	if (param->num_must_eat > 0)
		pthread_create(&thread, NULL, &is_everyone_full, param);
	i = -1;
	param->simul_start = get_time();
	while (++i < param->num_philo)
	{
		if (pthread_create(&param->tids[i], NULL, &life_start,
				&param->philo[i]) != 0)
			return (1);
		ft_usleep(1);
	}
	i = -1;
	while (++i < param->num_philo)
	{
		if (pthread_join(param->tids[i], NULL))
			return (1);
	}
	if (param->num_must_eat > 0)
		pthread_join(thread, NULL);
	return (0);
}
