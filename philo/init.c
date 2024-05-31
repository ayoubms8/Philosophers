/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:03:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 02:26:57 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo **philo, int argc, char **argv)
{
	int	i;

	i = 0;
	(void)argc;
	*philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!*philo)
		return (0);
	while (i < ft_atoi(argv[1]))
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_eat = 0;
		(*philo)[i].start = 0;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % ft_atoi(argv[1]);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv, t_philo *philo)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	data->nb_must_eat = -1;
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	data->philo = philo;
	data->forks = NULL;
	return (1);
}

int	init_mutex_andph(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nb_philo);
	if (!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL)
		|| pthread_mutex_init(&data->sleep, NULL)
		|| pthread_mutex_init(&data->eat, NULL)
		|| pthread_mutex_init(&data->dead, NULL)
		|| pthread_mutex_init(&data->done, NULL))
		return (0);
	i = -1;
	while (++i < data->nb_philo)
		philo[i].data = data;
	return (1);
}

void	done_eating(t_data *data)
{
	static int	done;

	done++;
	if (done == data->nb_philo)
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 0)
			data->is_dead = 1;
		pthread_mutex_unlock(&data->dead);
	}
}

int	take_forks(t_data *data, t_philo *philo)
{
	if (!check_death(data))
		return (0);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	if (!check_death(data))
		return (pthread_mutex_unlock(&data->forks[philo->left_fork]), 0);
	print_message(data, "has taken a fork", philo);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	if (!check_death(data))
		return (pthread_mutex_unlock(&data->forks[philo->right_fork]), 0);
	print_message(data, "has taken a fork", philo);
	return (1);
}
