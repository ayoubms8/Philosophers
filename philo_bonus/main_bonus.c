/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:40:14 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 17:02:02 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		kill(data->pid[i], SIGKILL);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("eat");
	if (argc < 5 || argc > 6)
		return (printf("Error: bad arguments\n"), 1);
	if (!check_args(argc, argv) || !init_data(&data, argc, argv))
		return (printf("Error: bad arguments\n"), 1);
	if (!init_philos(&data))
		return (printf("Error: bad arguments\n"), 1);
	if (!start_threads(&data))
		return (printf("Error: bad arguments\n"), 1);
	if (data.nb_eat != -1)
	{
		waitpid(-1, NULL, 0);
		usleep((data.time_to_eat + data.time_to_sleep) * 1000);
		sem_post(data.sem_death);
	}
	sem_wait(data.sem_death);
	kill_all(&data);
	clear_data(&data);
	exit(0);
}
