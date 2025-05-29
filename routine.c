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

void	*watchdog_routine()
{

}

void	*philosophers_routine(void *arg)
{
	t_philos	*philo;
	t_data		*data;

	data = philo->data;
	philo = (t_philos *)arg;
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_unlock(&data->write_lock);
	while(1)
	{
		pthread_mutex_lock(&data->stop_lock);
		if (data->is_stop)
		{
			pthread_mutex_unlock(&data->stop_lock);
			break;
		}
		pthread_mutex_unlock(&data->stop_lock);
		eat(); // to do
		sleep(); // to do
		think(); // to do
	}
	return (NULL);
}
