/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:31:15 by opopov            #+#    #+#             */
/*   Updated: 2025/05/29 13:02:09 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_start(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	data->start_time = get_current_time();
	pthread_mutex_lock(&data->write_lock);
	while (++i < data->num_of_phil)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philosophers_routine, &data->philos[i]) != 0)
			return (printf("Error: failed to create a philosopher thread\n"));
	}
	if (pthread_create(&monitor, NULL, watchdog_routine, data) != 0)
		return (printf("Error: failed to create a monitor thread\n"));
	pthread_mutex_unlock(&data->write_lock);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->num_of_phil)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}

int	data_init(t_data *data, char **argv, int argc)
{
	int	i;

	data->num_of_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_counter = ft_atoi(argv[5]);
	if (data->num_of_phil == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1
		|| (argc == 6 && data->eat_counter <= 0))
		return (printf("Error: invalid variables data\n"));
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->stop_lock, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_phil);
	if (!data->forks)
		return (printf("Error: fork allocation failed\n"));
	i = -1;
	while (++i < data->num_of_phil)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos = malloc(sizeof(t_philos) * data->num_of_phil);
	if (!data->philos)
	{
		free(data->forks);
		return (printf("Error: philosophers allocation failed\n"));
	}
	i = -1;
	while (++i < data->num_of_phil)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_of_phil];
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
	}
	data->is_stop = 0;
	data->start_time = get_current_time();
	return (0);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->forks)
	{
		while (++i < data->num_of_phil)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->stop_lock);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: invalid input\n"));
	memset(&data, 0, sizeof(t_data));
	if (data_init(&data, argv, argc) != 0)
		return (1);
	if (ft_start(&data) != 0)
	{
		free_all(&data);
		return (1);
	}
	free_all(&data);
	return (0);
}
