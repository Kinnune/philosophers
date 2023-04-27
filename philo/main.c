/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/27 15:45:03 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_philo	*philo_loop;
	t_rules	rules;
	int	full_philos;
	struct timeval start_clock;

	gettimeofday(&start_clock, NULL);
	if (parse_input(argc, argv, &rules) < 0)
		return (0);
	philos = set_table(&rules);
	philo_loop = philos;
	rules.start_clock = start_clock;
	rules.start_ms = timestamp(start_clock);
	pthread_mutex_init(&(rules.start_mutex), NULL);
	pthread_mutex_lock(&(rules.start_mutex));
	while(philos->id != rules.num_phil)
	{
		printf("creating thread %d\n", philos->id);
		// pthread_mutex_lock(&(philos->ate_mutex));
		pthread_create(&(philos->thread_id), NULL, life_of_philo, philos);
		philos = philos->next;
	}
	printf("creating thread %d\n", philos->id);
	pthread_create(&(philos->thread_id), NULL, life_of_philo, philos);
	full_philos = 0;
	pthread_mutex_lock(&(philos->ate_mutex));
	while ((timestamp(start_clock) - philo_loop->ate_at) < rules.ms_die && full_philos < rules.num_phil)
	{
		pthread_mutex_unlock(&(philo_loop->ate_mutex));
		if (philo_loop->id == 1)
			full_philos = 0;
		pthread_mutex_lock(&(philo_loop->ate_mutex));
		if (philo_loop->max_eat == 0)
			full_philos++;
		pthread_mutex_unlock(&(philo_loop->ate_mutex));
		philo_loop = philo_loop->next;
	}
	if (full_philos != rules.num_phil)
		printf("%lu %d died\n", timestamp(start_clock), philo_loop->id);
	return (0);
}
