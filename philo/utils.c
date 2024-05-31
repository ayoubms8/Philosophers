/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:24:16 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 15:27:40 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_data *data, char *message, t_philo *philo)
{
	long long	time;

	if (!check_death(data))
		return (0);
	pthread_mutex_lock(&data->print);
	if (!check_death(data))
		return (pthread_mutex_unlock(&data->print), 0);
	time = get_time();
	printf("%lld %d %s\n", time - philo->start, philo->id, message);
	pthread_mutex_unlock(&data->print);
	return (1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

int	eat(t_data *data, t_philo *philo)
{
	if (!check_death(data))
		return (0);
	print_message(data, "is eating", philo);
	pthread_mutex_lock(&data->eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&data->eat);
	ft_usleep(philo->data->time_to_eat, philo, data);
	philo->eat_count++;
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	return (1);
}

int	ft_sleep(t_data *data, t_philo *philo)
{
	if (!check_death(data))
		return (0);
	print_message(data, "is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep, philo, data);
	return (1);
}

int	ft_usleep(int time, t_philo *philo, t_data *data)
{
	long long	start;

	if (!check_death(data))
		return (0);
	start = get_time();
	while (get_time() - start < time)
	{
		usleep(200);
		pthread_mutex_lock(&data->sleep);
		if (!check_death(data))
			return (pthread_mutex_unlock(&data->sleep), 0);
		data->current_time = get_time();
		if (data->current_time - philo->last_eat > data->time_to_die)
			return (pthread_mutex_unlock(&data->sleep), philosopher_dead(data,
					philo), 0);
		pthread_mutex_unlock(&data->sleep);
	}
	return (1);
}
