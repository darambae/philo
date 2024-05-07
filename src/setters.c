/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:57:56 by dabae             #+#    #+#             */
/*   Updated: 2024/05/07 19:08:51 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_num_eat(t_philo *philo)
{
	mutex_handler(philo->data, &philo->num_eat_lock, LOCK);
	philo->num_eat++;
	mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
}

void	set_stop(t_data *data)
{
	mutex_handler(data, &data->exit_lock, LOCK);
	data->stop = true;
	mutex_handler(data, &data->exit_lock, UNLOCK);
}

void	set_eating(t_philo *philo, bool setting)
{
	mutex_handler(philo->data, &philo->eating_lock, LOCK);
	philo->is_eating = setting;
	mutex_handler(philo->data, &philo->eating_lock, UNLOCK);
}

void	set_start_time(t_philo *philo)
{
	uint64_t	cur_time;
	
	cur_time = get_time();
	mutex_handler(philo->data, &philo->start_time_lock, LOCK);
	philo->start_time = cur_time;
	mutex_handler(philo->data, &philo->start_time_lock, UNLOCK);
}
