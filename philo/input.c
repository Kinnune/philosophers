/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:27:23 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/19 13:00:14 by ekinnune         ###   ########.fr       */
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
		value += (*str) - '0';
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (value);
}

int	parse_input(int argc, char **argv, t_rules *rules)
{
	if (argc != 5 && argc != 6)
		return (-1);
	rules->num_phil = atoi_philo(*(argv + 1));
	rules->ms_die = atoi_philo(*(argv + 2));
	rules->ms_eat = atoi_philo(*(argv + 3));
	rules->ms_sleep = atoi_philo(*(argv + 4));
	if (rules->num_phil < 0 || rules->ms_die < 0
		|| rules->ms_eat < 0 || rules->ms_sleep < 0)
		return (-1);
	if (*(argv + 5))
	{
		rules->max_eat = atoi_philo(*(argv + 5));
		if (rules->max_eat < 0)
			return (-1);
	}
	else
		rules->max_eat = -1;
	return (0);
}
