/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:27:23 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/27 12:41:43 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	atoi_philo(const char *str)
{
	int	value;

	value = 0;
	if (!str)
		return (-1);
	while (*str == ' ' || *str == '\r' || *str == '\t'
		|| *str == '\n' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (value * 10 < value)
			return (-1);
		value *= 10;
		value += *str - '0';
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (value);
}

int	parse_input(int argc, char **argv, t_rules *rules)
{
	int	val_check;

	if (argc != 5 && argc != 6)
		return (-1);
	argv++;
	val_check = atoi_philo(*argv);
	if (val_check < 0)
		return (-1);
	rules->num_phil = val_check;
	argv++;
	val_check = atoi_philo(*argv);
	if (val_check < 0)
		return (-1);
	rules->ms_die = val_check;
	argv++;
	val_check = atoi_philo(*argv);
	if (val_check < 0)
		return (-1);
	rules->ms_eat = val_check;
	argv++;
	val_check = atoi_philo(*argv);
	if (val_check < 0)
		return (-1);
	rules->ms_sleep = val_check;
	argv++;
	if (*argv)
	{
		val_check = atoi_philo(*argv);
		if (val_check < 0)
			return (-1);
		rules->max_eat = val_check;
	}
	else
		rules->max_eat = -1;
	pthread_mutex_init(&rules->start_mutex, NULL);
	return (0);
}
