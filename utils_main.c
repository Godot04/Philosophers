/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:10:54 by opopov            #+#    #+#             */
/*   Updated: 2025/05/29 13:11:22 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo_status(t_philos *philo, char *status)
{
	t_data	*data;

	data =philo->data;
	pthread_mutex_lock(&data->write_lock);
	if (!data->is_stop)
		printf("%ld %d %s\n", get_current_time() - data->start_time, philo->id, status);
	pthread_mutex_unlock(&data->write_lock);
}

long	get_current_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	if (str[0] == '0')
		return (-1);
	res = 0;
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}
