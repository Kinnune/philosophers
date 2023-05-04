/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/04 11:51:51 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_rules			rules;
	pthread_mutex_t	start;

	rules.start_mutex = &start;
	gettimeofday(&(rules.start_clock), NULL);
	if (parse_input(argc, argv, &rules) < 0)
		return (0);
	philo = set_table(&rules);
	if (!philo)
		return (1);
	rules.start_ms = timestamp(rules.start_clock);
	pthread_mutex_init(rules.start_mutex, NULL);
	pthread_mutex_lock(rules.start_mutex);
	if (create_threads(philo, &rules) < 0)
		return (1);
	pthread_mutex_unlock(rules.start_mutex);
	monitor_loop(philo, &rules);
	return (0);
}
