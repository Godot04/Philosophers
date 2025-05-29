/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:04:42 by opopov            #+#    #+#             */
/*   Updated: 2025/05/29 13:11:12 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data t_data;

typedef struct s_philos
{
	int				id;
	int				is_dead;
	int				last_meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread;
	t_data			*data;
}					t_philos;

typedef struct s_data
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	stop_lock;
	t_philos		*philos;
	int				is_stop;
	long			start_time;
}					t_data;

int		ft_atoi(char *str);
long	get_current_time();
void	*philosophers_routine(void *arg);
void	*watchdog_routine();
void	print_philo_status(t_philos *philo, char *status);


#endif
