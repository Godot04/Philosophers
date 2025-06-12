/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:00:32 by opopov            #+#    #+#             */
/*   Updated: 2025/05/29 13:18:54 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philos **philo)
{
	t_data	*data;

	data = (*philo)->data;
	pthread_mutex_lock(&data->meal_lock);
	print_philo_status((*philo), "is eating");
	(*philo)->last_meal_time = get_current_time();
	(*philo)->meals_eaten++;
	pthread_mutex_unlock(&data->meal_lock);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock((*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
}

void	sleep(t_philos *philo)
{
	t_data *data = philo->data;
	print_philo_status(philo, "is sleeping");
	usleep(data->time_to_sleep * 1000);
}

void	think(t_philos *philo)
{
	print_philo_status(philo, "is thinking");
}
