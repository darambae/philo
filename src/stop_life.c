/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:26:05 by dabae             #+#    #+#             */
/*   Updated: 2024/05/13 10:36:46 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	set_stop(t_philo *phi)
{
	phi->state = DEAD;
	pthread_mutex_unlock(&phi->lock);
	print(phi, "died");
	pthread_mutex_lock(&phi->param->lock);
	phi->param->stop = 1;
	pthread_mutex_unlock(&phi->param->lock);
}

int	check_exit(t_philo *phi)
{
	pthread_mutex_lock(&phi->param->lock);
	if (phi->param->stop)
	{
		pthread_mutex_unlock(&phi->param->lock);
		return (1);
	}
	pthread_mutex_unlock(&phi->param->lock);
	return (0);
}

/*check if any philopher died*/
void	*anyone_dead(void *philo)
{
	t_philo		*phi;

	phi = (t_philo *)philo;
	while (1)
	{
		if (check_exit(phi))
			break ;
		pthread_mutex_lock(&phi->lock);
		if (phi->num_eat && get_time() >= phi->time_limit_to_death \
			&& phi->state != EAT)
		{
			set_stop(phi);
			break ;
		}
		if (get_time() >= phi->param->simul_start + phi->param->time_to_die \
			&& phi->num_eat == 0 && phi->state != EAT)
		{
			set_stop(phi);
			break ;
		}
		pthread_mutex_unlock(&phi->lock);
		ft_usleep(10);
	}
	ft_usleep(100);
	return ((void *)0);
}

void	*is_everyone_full(void *param)
{
	t_param	*data;

	data = (t_param *)param;
	pthread_mutex_lock(&data->lock);
	while (data->stop == 0 && data->num_full < data->num_philo)
	{
		pthread_mutex_unlock(&data->lock);
		ft_usleep(100);
		pthread_mutex_lock(&data->lock);
	}
	if (data->stop == 0 && data->num_full >= data->num_philo)
	{
		pthread_mutex_lock(&data->print);
		printf("Everyone has eaten at least %d times\n", data->num_must_eat);
		pthread_mutex_unlock(&data->print);
		data->stop = 1;
		pthread_mutex_unlock(&data->lock);
		return (NULL);
	}
	else
		pthread_mutex_unlock(&data->lock);
	ft_usleep(50);
	return (NULL);
}
