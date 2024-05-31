/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 02:49:43 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 19:00:12 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	print_status(philo, FORK);
	sem_wait(philo->data->sem_forks);
	print_status(philo, FORK);
}

void	eat(t_philo *philo)
{
	print_status(philo, EAT);
	philo->last_eat = get_time();
	ft_usleep(philo->data->time_to_eat, philo, philo->data);
	philo->nb_eat++;
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_eat >= philo->data->time_to_die)
		{
			print_status(philo, DEAD);
			sem_post(philo->data->sem_death);
			exit(0);
		}
	}
	return (NULL);
}

int	philo(t_philo *philo)
{
	philo->check = malloc(sizeof(pthread_t));
	if (pthread_create(&philo->check, NULL, check_death, philo))
		return (0);
	if (pthread_detach(philo->check))
		return (0);
	philo->last_eat = philo->data->start_time;
	while (1)
	{
		if (philo->data->nb_eat != -1 && philo->nb_eat == philo->data->nb_eat)
			exit(0);
		take_forks(philo);
		eat(philo);
		print_status(philo, SLEEP);
		ft_usleep(philo->data->time_to_sleep, philo, philo->data);
		print_status(philo, THINK);
	}
	return (1);
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			philo(&data->philo[i]);
		else if (data->pid[i] < 0)
			return (0);
		i++;
	}
	return (1);
}
