/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:41:16 by dabae             #+#    #+#             */
/*   Updated: 2024/04/30 10:36:32 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_handler(t_data *data, pthread_mutex_t *mutex, int type)
{
	if (type == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			return (ft_exit(data, 1, "Failed to initialize mutex"));
	}
	else if (type == DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			return (ft_exit(data, 1, "Failed to destroy mutex"));
	}
	else if (type == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (ft_exit(data, 1, "Failed to lock mutex"));
	}
	else if (type == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			return (ft_exit(data, 1, "Failed to unlock mutex"));
	}
}

void	print(t_philo *philo, char *str)
{
	mutex_handler(philo->data, &philo->data->print_lock, LOCK);
	printf("%lu %d %s\n", get_time(), philo->id, str);
	mutex_handler(philo->data, &philo->data->print_lock, UNLOCK);
}