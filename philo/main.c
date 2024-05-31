/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:16:02 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 16:34:41 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->done);
	done_eating(philo->data);
	pthread_mutex_unlock(&philo->data->done);
}

void	*routine(void *philoo)
{
	t_philo	*philo;

	philo = ((t_philo *)philoo);
	pthread_mutex_lock(&philo->data->eat);
	philo->last_eat = philo->start;
	pthread_mutex_unlock(&philo->data->eat);
	if (!(philo->id % 2))
		usleep(10000);
	while (1)
	{
		if (!check_death(philo->data))
			return (NULL);
		if (philo->data->nb_must_eat != -1
			&& philo->eat_count == philo->data->nb_must_eat)
			return (check_eat(philo), NULL);
		take_forks(philo->data, philo);
		eat(philo->data, philo);
		if (philo->data->nb_must_eat != -1
			&& philo->eat_count == philo->data->nb_must_eat)
			return (check_eat(philo), NULL);
		ft_sleep(philo->data, philo);
		print_message(philo->data, "is thinking", philo);
	}
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].start = get_time();
		data->philo[i].last_eat = data->philo[i].start;
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				&data->philo[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_detach(data->philo[i].thread))
			return (0);
		i++;
	}
	if (pthread_create(&data->death_monitor, NULL, death_monitor, data))
		return (0);
	if (pthread_join(data->death_monitor, NULL))
		return (0);
	return (1);
}

int	do_the_rest(t_data *data, t_philo **philo, int argc, char **argv)
{
	if (init_data(data, argc, argv, *philo))
	{
		if (init_mutex_andph(data, *philo))
		{
			if (start_threads(data))
				return (1);
			else
				printf("Error: Failed to create threads\n");
		}
		else
			printf("Error: Failed to create mutex\n");
	}
	else
		printf("Error: Failed allocation\n");
	return (0);
}
void v()
{
	system("leaks philo");
}
int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	int		vld;
atexit(v);
	philo = NULL;
	vld = valid_args(argc, argv);
	if (vld != 1)
	{
		if (vld != 2)
		{
			if (init_philo(&philo, argc, argv))
			{
				if (do_the_rest(&data, &philo, argc, argv))
					return (usleep((data.time_to_eat + data.time_to_sleep)
							* 1000), destroy_mutex(&data), 0);
			}
			else
				printf("Error: Failed allocation\n");
		}
		else
			printf("Error: Wrong arguments\n");
	}
	else
		printf("Error: Wrong number of arguments\n");
	return (1);
}
