/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:26:25 by dabae             #+#    #+#             */
/*   Updated: 2024/05/01 15:08:14 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*allocating memory for forks, philosophers and thread in parameters*/
static int	allocate_data(t_data *data)
{
	int	i;

	i = -1;
	data->tids = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->tids)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (1);
	while (++i < data->num_philo)
	{
		mutex_handler(data, &data->philo[i].num_eat_lock, INIT);
		mutex_handler(data, &data->philo[i].eating_lock, INIT);
		mutex_handler(data, &data->philo[i].last_meal_lock, INIT);
		mutex_handler(data, &data->philo[i].start_time_lock, INIT);
		mutex_handler(data, &data->forks[i], INIT);
	}
	return (0);
}

/*Initializing the dataeters*/
void	init_data(t_data *data, char **args)
{
	if (is_digit(args) && is_positive(args))
	{
		mutex_handler(data, &data->print_lock, INIT);
		mutex_handler(data, &data->stop_lock, INIT);
		mutex_handler(data, &data->full_lock, INIT);
		mutex_handler(data, &data->monitor_lock, INIT);
		data->stop = 0;
		data->num_full = 0;
		data->num_philo = (int) ft_atoi(args[0]);
		data->time_to_die = (uint64_t) ft_atoi(args[1]);
		data->time_to_eat = (uint64_t) ft_atoi(args[2]);
		data->time_to_sleep = (uint64_t) ft_atoi(args[3]);
		if (args[4] && ft_atoi(args[4]) > 0)
			data->num_must_eat = (int) ft_atoi(args[4]);
		else
			data->num_must_eat = -1;
		if (allocate_data(data) == 1)
			ft_exit(data, 1, "Failed allocation of dataeters");
	}
	else
	{
		free(data);
		printf("ERROR : Double check arguments\n");
		exit(1);
	}
}

/*Initializing philosophers*/
int	init_philo(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].num_eat = 0;
		data->philo[i].is_full = false;
		data->philo[i].is_eating = 0;
		data->philo[i].start_time = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].left_fork = &data->forks[i];
		if (data->num_philo == 1)
			data->philo[i].right_fork = NULL;
		else if (i == 0)
			data->philo[i].right_fork = &data->forks[data->num_philo - 1];
		else
			data->philo[i].right_fork = &data->forks[i - 1];
	}
	return (0);
}
