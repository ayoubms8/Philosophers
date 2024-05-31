/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:48:06 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 03:15:29 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->sleep);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->done);
	free(data->forks);
	free(data->philo);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	philosopher_dead(t_data *data, t_philo *philo)
{
	print_message(data, "died", philo);
	pthread_mutex_lock(&data->dead);
	if (data && data->is_dead == 0)
		data->is_dead = 1;
	pthread_mutex_unlock(&data->dead);
}

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead)
		return (pthread_mutex_unlock(&data->dead), 0);
	pthread_mutex_unlock(&data->dead);
	return (1);
}

void	*death_monitor(void *dataa)
{
	t_data	*data;
	int		i;

	data = ((t_data *)dataa);
	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (!check_death(data))
				return (NULL);
			pthread_mutex_lock(&data->sleep);
			if (!check_death(data))
				return (pthread_mutex_unlock(&data->sleep), NULL);
			data->current_time = get_time();
			pthread_mutex_lock(&data->eat);
			if (data->current_time
				- data->philo[i].last_eat > data->time_to_die)
				return (pthread_mutex_unlock(&data->sleep),
					pthread_mutex_unlock(&data->eat), philosopher_dead(data,
						&data->philo[i]), NULL);
			pthread_mutex_unlock(&data->eat);
			pthread_mutex_unlock(&data->sleep);
		}
	}
}
