/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/25 10:27:35 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *life_of_philo(void *args)
{
	t_philo *philo = (t_philo *)args;
	t_rules rules = *(philo->rules);


	// pthread_mutex_lock(&(rules.start_mutex));
	// pthread_mutex_unlock(&(rules.start_mutex));
	if (philo->id & 1)
		mssleep(5);
	while (1)
	{
		if (philo->id & 1)
		{
			pthread_mutex_lock(philo->left);
			printf("%lu %u has taken a fork left\n", timestamp(rules.start_clock), philo->id);
			pthread_mutex_lock(philo->right);
			printf("%lu %u has taken a fork right\n", timestamp(rules.start_clock), philo->id);
		}
		else
		{
			pthread_mutex_lock(philo->right);
			printf("%lu %u has taken a fork right\n", timestamp(rules.start_clock), philo->id);
			pthread_mutex_lock(philo->left);
			printf("%lu %u has taken a fork left\n", timestamp(rules.start_clock), philo->id);
		}
		printf("%lu %u is eating\n", timestamp(rules.start_clock), philo->id);
		pthread_mutex_lock(&(philo->ate_mutex));
		philo->ate_at = timestamp(rules.start_clock);
		if (philo->max_eat > 0)
			philo->max_eat--;
		pthread_mutex_unlock(&(philo->ate_mutex));
		mssleep(rules.ms_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%lu %u is sleeping\n", timestamp(rules.start_clock), philo->id);
		mssleep(rules.ms_sleep);
		printf("%lu %u is thinking\n", timestamp(rules.start_clock), philo->id);
		// mssleep(1);
	}
	return (NULL);
}

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
printf("num_phil = %d, time_die = %d, time_eat = %d, time_sleep = %d, must_eat = %d\n",
rules.num_phil, rules.ms_die, rules.ms_eat, rules.ms_sleep, rules.max_eat);

	philos = set_table(&rules);
	philo_loop = philos;
	rules.start_clock = start_clock;
	rules.start_ms = timestamp(start_clock);
	pthread_mutex_lock(&(rules.start_mutex));
	while(philos->id != rules.num_phil)
	{
		printf("creating thread %d\n", philos->id);
		pthread_create(&(philos->thread_id), NULL, life_of_philo, philos);
		philos = philos->next;
	}
	printf("creating thread %d\n", philos->id);
	pthread_create(&(philos->thread_id), NULL, life_of_philo, philos);
	pthread_mutex_unlock(&(rules.start_mutex));
	pthread_mutex_lock(&(philo_loop->ate_mutex));
	full_philos = 0;
	while ((timestamp(start_clock) - philo_loop->ate_at) < rules.ms_die || full_philos < rules.num_phil)
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
// 	printf("test\n");
	if (full_philos == rules.num_phil)
		printf("%lu everone finished", timestamp(start_clock));		
	else
		printf("%lu %d died\n", timestamp(start_clock), philo_loop->id);
	return (0);
}
