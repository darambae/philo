/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:26:18 by dabae             #+#    #+#             */
/*   Updated: 2024/04/30 09:45:38 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_full(t_philo *philo)
{
	mutex_handler(philo->data, &philo->num_eat_lock, LOCK);
	if (philo->num_eat == philo->data->num_must_eat)
	{
		mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
		return (1);
	}
	mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
	return (0);
}

// int	is_everyone_full(t_data *data)
// {
// 	if (check_full(data))
// 	{
// 		set_stop(data);
// 		printf("Everyone is full\n");
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

void	check_death(t_philo *philo)
{
	if (philo->data->num_philo == 1)
	{
		//change_state(philo, DEAD);
		print(philo, "died");
		philo->data->stop = true;
		return ;
	}
	mutex_handler(philo->data, &philo->last_meal_lock, LOCK);
	if (philo->last_meal && get_time() >= philo->last_meal + philo->data->time_to_die)
	{
		//change_state(philo, DEAD);
		print(philo, "died");
		philo->data->stop = true;
	}
	mutex_handler(philo->data, &philo->last_meal_lock, UNLOCK);
	// mutex_handler(philo->data, &philo->num_eat_lock, LOCK);
	// if (philo->num_eat == 0)
	// {
	// 	time = philo->data->start_time;
	// 	mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
	// }
	// else
	// {
	// 	mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
	// 	mutex_handler(philo->data, &philo->last_meal_lock, LOCK);
	// 	time = philo->last_meal;
	// 	mutex_handler(philo->data, &philo->last_meal_lock, UNLOCK);
	// }
	// if (time + philo->data->time_to_die < get_time())
	// {
	// 	//change_state(philo, DEAD);
	// 	print(philo, "died");
	// 	philo->data->stop = true;
	// }
	// mutex_handler(philo->data, &philo->num_eat_lock, LOCK);
	// if (philo->num_eat == 0)
	// {
	// 	if (philo->data->start_time + philo->data->time_to_die < get_time())
	// 	{
	// 		//change_state(philo, DEAD);
	// 		print(philo, "died");
	// 		philo->data->stop = true;
	// 	}
	// 	mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);
	// }
	// else
	// {
	// 	mutex_handler(philo->data, &philo->last_meal_lock, LOCK);
	// 	if (get_time() >= philo->last_meal + philo->data->time_to_die)
	// 	{
	// 		//change_state(philo, DEAD);
	// 		print(philo, "died");
	// 		philo->data->stop = true;
	// 	}
	// 	mutex_handler(philo->data, &philo->last_meal_lock, UNLOCK);
	// }
	//mutex_handler(philo->data, &philo->num_eat_lock, UNLOCK);

}

// int	is_anyone_dead(t_philo *philo)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < philo->data->num_philo)
// 	{
// 		if (check_death(philo))
// 		{
// 			set_stop(philo->data);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

void	check_to_stop(t_data *data)
{
	int	i;
	int	full_count;

	full_count = 0;
	while (1)
	{
		i = -1;
		while (++i < data->num_philo)
		{
			if (data->num_must_eat > 0)
				full_count += check_full(&data->philo[i]);
			mutex_handler(data, &data->stop_lock, LOCK);
			if (full_count == data->num_philo)
			{
				mutex_handler(data, &data->print_lock, LOCK);
				printf("All have eaten as many times as %d.\n", data->num_must_eat);
				mutex_handler(data, &data->print_lock, UNLOCK);
				data->stop = true;
				mutex_handler(data, &data->stop_lock, UNLOCK);
				return ;
			}
			check_death(&data->philo[i]);
			if (data->stop)
			{
				mutex_handler(data, &data->stop_lock, UNLOCK);
				return ;
			}
			mutex_handler(data, &data->stop_lock, UNLOCK);
		}
	}
}
