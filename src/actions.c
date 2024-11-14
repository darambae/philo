/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:48:17 by dabae             #+#    #+#             */
/*   Updated: 2024/05/13 09:21:40 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	change_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->lock);
	if (state == DEAD)
	{
		pthread_mutex_lock(&philo->param->lock);
		philo->param->stop = 1;
		pthread_mutex_unlock(&philo->param->lock);
	}
	else if (state == EAT)
		philo->time_limit_to_death = get_time() + philo->param->time_to_die;
	philo->state = state;
	pthread_mutex_unlock(&philo->lock);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->param->lock);
	if (philo->param->stop)
	{
		pthread_mutex_unlock(&philo->param->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->param->lock);
	pthread_mutex_lock(&philo->lock);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->lock);
	if (philo->state == FULL)
	{
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

/*By taking forks, start to eat*/
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (!check_stop(philo))
		print(philo, "has taken a fork");
}

/*by putting down forks, stop eating*/
void	put_down_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->num_eat++;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
