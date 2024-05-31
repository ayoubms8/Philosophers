/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:12:57 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/17 01:23:38 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9') || !ft_atoi(argv[i]))
				return (2);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	int		sign;
	long	acc;
	long	start;

	i = 0;
	sign = 1;
	acc = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	start = i;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
		acc = acc * 10 + (str[i++] - '0');
	if (i - start >= 19)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (acc * sign);
}
