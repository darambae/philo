/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:26:27 by dabae             #+#    #+#             */
/*   Updated: 2024/04/29 14:07:20 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		ft_usleep(3000);
		mutex_handler(philo->data, philo->right_fork, LOCK);
	}
	else
		mutex_handler(philo->data, philo->left_fork, LOCK);
	if (!time_to_stop(philo))
		print(philo, "has taken a fork");
	if (philo->id % 2 == 0)
	{
		ft_usleep(3000);
		mutex_handler(philo->data, philo->left_fork, LOCK);
	}
	else
		mutex_handler(philo->data, philo->right_fork, LOCK);
	if (!time_to_stop(philo))
		print(philo, "has taken a fork");
	return (0);
}

void	eat(t_philo *philo)
{
	print(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	//change_state(philo, EATING);
	set_last_meal(philo);
	set_num_eat(philo);
	// mutex_handler(philo->data, &philo->num_eat_lock, LOCK);
	// printf("At %lu, Philosopher no.%d has eaten %d times.\n", get_time(), philo->id, philo->num_eat);
	// mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
	mutex_handler(philo->data, philo->left_fork, UNLOCK);
	mutex_handler(philo->data, philo->right_fork, UNLOCK);
}

void	sleep_phase(t_philo *philo)
{
	//change_state(philo, SLEEPING);
	print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	//change_state(philo, THINKING);
	print(philo, "is thinking");
}
