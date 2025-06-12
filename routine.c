/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:06:14 by opopov            #+#    #+#             */
/*   Updated: 2025/05/29 13:06:30 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*watchdog_routine(void *arg)
{
	t_philos	*philo;
	t_data		*data;
	int i;

	philo = (t_philos *)arg;
	data = philo->data;
	while (1)
	{
		i = -1;
		while (++i < data->num_of_phil)
		{
			pthread_mutex_lock(&data->meal_lock);
			if (get_current_time() - data->philos[i]->last_meal_time > data->time_to_die)
			{
				pthread_mutex_unlock(&data->meal_lock);
				pthread_mutex_lock(&data->write_lock);
				printf("%ld %d is died\n", get_current_time() - data->start_time, data->philos->id);
				pthread_mutex_unlock(&data->write_lock);
				pthread_mutex_lock(&data->is_stop);
				data->is_stop = 1;
				pthread_mutex_unlock(&data->is_stop);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_lock);
			if (data->eat_counter == philo->meals_eaten)
			{
				pthread_mutex_lock(&data->is_stop);
				data->is_stop = 1;
				pthread_mutex_unlock(&data->is_stop);
				return (NULL);
			}
			usleep(1000);
		}
	}
}

void	*philosophers_routine(void *arg)
{
	t_philos	*philo;
	t_data		*data;

	philo = (t_philos *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_unlock(&data->write_lock);
	if (data->num_of_phil == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo_status(philo, "has taken a fork");
		usleep(data->time_to_die * 1000);
		print_philo_status(philo, "died");
		return (NULL);
	}
	while(1)
	{
		pthread_mutex_lock(&data->stop_lock);
		if (data->is_stop)
		{
			pthread_mutex_unlock(&data->stop_lock);
			break;
		}
		pthread_mutex_unlock(&data->stop_lock);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print_philo_status(philo, "has taken a left fork");
			pthread_mutex_lock(philo->right_fork);
			print_philo_status(philo, "has taken a right fork");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print_philo_status(philo, "has taken a right fork");
			pthread_mutex_lock(philo->left_fork);
			print_philo_status(philo, "has taken a left fork");
		}
		eat(&philo); 
		sleep(philo); 
		think(philo);
	}
	return (NULL);
}
