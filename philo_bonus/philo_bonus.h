/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:39:48 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 15:35:51 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3
# define FORK 4

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				dead;
	int				start_time;
	int				*pid;
	sem_t			*sem_forks;
	sem_t			*sem_death;
	sem_t			*sem_print;
	sem_t			*sem_eat;
	struct s_philo	*philo;
}t_data;

typedef struct s_philo
{
	pthread_t		check;
	int				id;
	int				nb_eat;
	int				last_eat;
	int				status;
	t_data			*data;	
}t_philo;

int		init_philos(t_data *data);
int		init_data(t_data *data, int argc, char **argv);
int		get_time(void);
int		ft_atoi(const char *str);
void	clear_data(t_data *data);
void	print_status(t_philo *philo, int status);
void	ft_usleep(int time, t_philo *philo, t_data *data);
void	one_philo(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	*check_death(void *arg);
int		philo(t_philo *philo);
int		start_threads(t_data *data);

#endif