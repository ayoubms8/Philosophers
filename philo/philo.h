/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:15:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/21 03:15:38 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_dead;
	int				eat_count;
	long long		last_eat;
	long long		start;
	int				left_fork;
	int				right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_t		death_monitor;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_dead;
	int				nb_must_eat;
	int				id;
	long long		current_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	sleep;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	done;
}					t_data;

int			ft_atoi(const char *str);
int			print_message(t_data *data, char *message, t_philo *philo);
int			init_data(t_data *data, int argc, char **argv, t_philo *philo);
int			init_philo(t_philo **philo, int argc, char **argv);
int			init_mutex_andph(t_data *data, t_philo *philo);
int			eat(t_data *data, t_philo *philo);
int			ft_usleep(int time, t_philo *philo, t_data *data);
void		philosopher_dead(t_data *data, t_philo *philo);
long long	get_time(void);
int			ft_sleep(t_data *data, t_philo *philo);
void		destroy_mutex(t_data *data);
void		one_philo(t_philo *philo);
void		philosopher_dead(t_data *data, t_philo *philo);
int			check_death(t_data *data);
void		done_eating(t_data *data);
int			take_forks(t_data *data, t_philo *philo);
int			valid_args(int argc, char **argv);
void		*death_monitor(void *dataa);
int			ft_strcmp(const char *s1, const char *s2);

#endif