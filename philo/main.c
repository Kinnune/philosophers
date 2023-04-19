/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/19 16:10:26 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *life_of_philo(void *args)
{
	t_philo *philo = (t_philo *)args;
	t_rules rules = *(philo->rules);

	while (1)
	{
		if (philo->id & 1)
		{
			pthread_mutex_lock(philo->left);
			printf("%lu %u has taken a fork\n", timestamp(rules.start_clock), philo->id);
			pthread_mutex_lock(philo->right);
			printf("%lu %u has taken a fork\n", timestamp(rules.start_clock), philo->id);
		}
		else
		{
			pthread_mutex_lock(philo->right);
			printf("%lu %u has taken a fork\n", timestamp(rules.start_clock), philo->id);
			pthread_mutex_lock(philo->left);
			printf("%lu %u has taken a fork\n", timestamp(rules.start_clock), philo->id);
		}
		printf("%lu %u is eating\n", timestamp(rules.start_clock), philo->id);
		mssleep(rules.ms_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_lock(&(philo->ate_mutex));
		philo->ate_at = timestamp(rules.start_clock);
		pthread_mutex_unlock(&(philo->ate_mutex));
		printf("%lu %u is sleeping\n", timestamp(rules.start_clock), philo->id);
		mssleep(rules.ms_sleep);
		printf("%lu %u is thinking\n", timestamp(rules.start_clock), philo->id);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_philo	*philo_loop;
	t_rules	rules;
	struct timeval start_clock;

	gettimeofday(&start_clock, NULL);
	if (parse_input(argc, argv, &rules) < 0)
		return (0);
printf("num_phil = %d, time_die = %d, time_eat = %d, time_sleep = %d, must_eat = %d\n",
rules.num_phil, rules.ms_die, rules.ms_eat, rules.ms_sleep, rules.max_eat);

	philos = set_table(&rules);
	philo_loop = philos;
	rules.start_clock = start_clock;
	rules.start_ms = timestamp(start_clock);
	while(philos->id != rules.num_phil)
	{
		printf("creating thread %d\n", philos->id);
		pthread_create(&(philos->thread_id), NULL, life_of_philo, philos);
		philos = philos->next;
	}
	printf("creating thread %d\n", philos->id);
	pthread_create(&(philos->thread_id), NULL, life_of_philo, philos);
	pthread_mutex_lock(&(philo_loop->ate_mutex));
	while (timestamp(start_clock) - philo_loop->ate_at < rules.ms_die)
	{
		pthread_mutex_unlock(&(philo_loop->ate_mutex));
		philo_loop = philo_loop->next;
		pthread_mutex_lock(&(philo_loop->ate_mutex));
	}
	printf("%lu %d died\n", timestamp(start_clock), philo_loop->id);
	return (0);
}
