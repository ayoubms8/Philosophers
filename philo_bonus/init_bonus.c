/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:13:12 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 19:00:44 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_eat = -1;
	data->dead = 0;
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	if (data->nb_philo < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || (argc == 6 && data->nb_eat < 1))
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (0);
	data->pid = malloc(sizeof(int) * data->nb_philo);
	if (!data->pid)
		return (0);
	data->sem_forks = sem_open("forks", O_CREAT, 0644, data->nb_philo);
	data->sem_death = sem_open("death", O_CREAT, 0644, 0);
	data->sem_print = sem_open("print", O_CREAT, 0644, 1);
	data->sem_eat = sem_open("eat", O_CREAT, 0644, 1);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_eat = 0;
		data->philo[i].last_eat = 0;
		data->philo[i].status = THINK;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}
