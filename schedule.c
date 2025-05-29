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

void	eat(t_philos *philo)
{
	t_data	*data;

	data = philo->data;
	// take forks
	pthread_mutex_lock(philo->left_fork);
	print_philo_status(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	print_philo_status(philo, "has taken a right fork");
	// eat
	pthread_mutex_lock(&data->meal_lock);
	print_philo_status(philo, "is eating");
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&data->meal_lock);
	usleep(data->time_to_eat * 1000);
	// return forks to the start position
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep()
{

}

void	think()
{

}
