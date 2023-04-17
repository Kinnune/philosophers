/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/17 14:52:34 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void life_of_philo(t_philo philo, t_rules rules)
{
	unsigned long action_start_ms;
	if (philo.id & 1)
	{
		pthread_mutex_lock(philo.left);
		printf("%u %u has taken a fork", timestamp(rules.start_clock), philo.id);
		pthread_mutex_lock(philo.right);
		printf("%u %u has taken a fork", timestamp(rules.start_clock), philo.id);
	}
	else
	{
		pthread_mutex_lock(philo.right);
		printf("%u %u has taken a fork", timestamp(rules.start_clock), philo.id);
		pthread_mutex_lock(philo.left);
		printf("%u %u has taken a fork", timestamp(rules.start_clock), philo.id);
	}
	action_start_ms = timestamp(rules.start_clock);
	printf("%lu %u is eating", action_start_ms, philo.id);

	// while time since eaten < time since started eating - ms_from_start
	// while(ms_from_start(rules.start_time))
	//sleep(time_to_eat)
	action_start_ms = timestamp(rules.start_clock);
	printf("%lu %u is sleeping", action_start_ms, philo.id);
	printf("%u %u is thinking", timestamp(rules.start_clock), philo.id);
	life_of_philo(philo, rules);
}

int	main(int argc, char **argv)
{
	pthread_t thread_id[201];
	t_philo	*philos;
	t_fork	*forks;
	t_rules	rules;
	struct timeval start_clock;
	unsigned long start_ms;
	unsigned long current_ms;

// 	if (parse_input(argc, argv, &rules) < 0)
// 		return (0);
// 	philos = set_table(forks, &rules);
	pthread_mutex_init(&test_lock, NULL);
	gettimeofday(&start_clock, NULL);
	rules.start_clock = start_clock;
	rules.start_ms = timestamp(start_clock);

	pthread_create(&thread_id[0], NULL, test_print, NULL);
	pthread_join(thread_id[0], NULL);
	return (0);
}
// 	sleep(5);
// gettimeofday(&clock, NULL);
// current_ms = (clock.tv_sec + (clock.tv_usec / 1000000)) - start_ms;
// printf("clock tv_sec = %li\nclock tv_usec = %i\nstart_ms = %li\ncurrent_ms = %li\n", clock.tv_sec, clock.tv_usec, start_ms, current_ms);

// printf("num_phil = %d, time_die = %d, time_eat = %d, time_sleep = %d, must_eat = %d\n",
// rules.num_phil, rules.ms_die, rules.ms_eat, rules.ms_sleep, rules.max_eat);

// 	while(philos->id != rules.num_phil)
// 	{
// 		printf("%d\n", philos->id);
// 		philos = philos->next;
// 	}
// 	printf("%d\n", philos->id);
