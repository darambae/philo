/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:26:27 by dabae             #+#    #+#             */
/*   Updated: 2024/05/06 17:56:02 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		mutex_handler(philo->data, philo->right_fork, LOCK);
	else
		mutex_handler(philo->data, philo->left_fork, LOCK);
	if (!time_to_stop(philo))
		print(philo, "has taken a fork");
	if (philo->id % 2 == 0)
		mutex_handler(philo->data, philo->left_fork, LOCK);
	else
		mutex_handler(philo->data, philo->right_fork, LOCK);
	if (!time_to_stop(philo))
		print(philo, "has taken a fork");
	set_start_time(philo, get_time());
	return (0);
}

int	unlock_forks(t_philo *philo)
{
	if (time_to_stop(philo))
	{
		mutex_handler(philo->data, philo->left_fork, UNLOCK);
		mutex_handler(philo->data, philo->right_fork, UNLOCK);
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	print(philo, "is eating");
	set_eating(philo, 1);
	ft_usleep(philo->data->time_to_eat);
	set_num_eat(philo);
	mutex_handler(philo->data, philo->left_fork, UNLOCK);
	mutex_handler(philo->data, philo->right_fork, UNLOCK);
}

void	sleep_phase(t_philo *philo)
{
	set_eating(philo, 0);
	print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print(philo, "is thinking");
}
