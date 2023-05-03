/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/03 14:56:56 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_philo *philo, t_rules *rules)
{
	while (philo->id != rules->num_phil)
	{
		if (pthread_create(&(philo->thread_id), NULL, life_of_philo, philo))
			return (-1);
		philo = philo->next;
	}
	if (pthread_create(&(philo->thread_id), NULL, life_of_philo, philo))
		return (-1);
	return (0);
}

void	monitor_loop(t_philo *philo, t_rules *rules)
{
	int	full_philos;

	full_philos = 0;
	pthread_mutex_lock(&(philo->ate_mutex));
	while ((int)(timestamp(rules->start_clock) - philo->ate_at) < rules->ms_die
		&& full_philos < rules->num_phil)
	{
		pthread_mutex_unlock(&(philo->ate_mutex));
		if (philo->id == 1)
			full_philos = 0;
		pthread_mutex_lock(&(philo->ate_mutex));
		if (philo->max_eat == 0)
			full_philos++;
		pthread_mutex_unlock(&(philo->ate_mutex));
		philo = philo->next;
		usleep(10);
	}
	if (full_philos != rules->num_phil)
		printf("%lu %d died\n", timestamp(rules->start_clock), philo->id);
}

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
	rules.start_ms = timestamp(rules.start_clock);
	pthread_mutex_init(rules.start_mutex, NULL);
	pthread_mutex_lock(rules.start_mutex);
	if (create_threads(philo, &rules) < 0)
		return (0);
	pthread_mutex_unlock(rules.start_mutex);
	monitor_loop(philo, &rules);
	return (0);
}
