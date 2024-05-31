/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 22:14:38 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 19:00:02 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clear_data(t_data *data)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_death);
	sem_close(data->sem_print);
	sem_close(data->sem_eat);
	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("eat");
	free(data->philo);
	free(data->pid);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		n = n * 10 + (str[i++] - '0');
	return (n * sign);
}

int	get_time(void)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	ft_usleep(int time, t_philo *philo, t_data *data)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (get_time() - philo->last_eat >= data->time_to_die)
		{
			print_status(philo, DEAD);
			sem_post(data->sem_death);
			exit(0);
		}
		usleep(200);
	}
}

void	print_status(t_philo *philo, int status)
{
	int	time;

	sem_wait(philo->data->sem_print);
	time = get_time() - philo->data->start_time;
	if (status == FORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	else if (status == EAT)
		printf("%d %d is eating\n", time, philo->id);
	else if (status == SLEEP)
		printf("%d %d is sleeping\n", time, philo->id);
	else if (status == THINK)
		printf("%d %d is thinking\n", time, philo->id);
	else if (status == DEAD)
	{
		printf("%d %d died\n", time, philo->id);
		return ;
	}
	sem_post(philo->data->sem_print);
}
