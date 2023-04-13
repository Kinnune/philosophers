/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/13 11:15:37 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int test = 0;
pthread_mutex_t test_lock;

void	*test_print()
{
	pthread_mutex_lock(&test_lock);
	for (int i = 0; i < 10; i++)
	{
		test += 1;
		printf("%d\n", test);
	}
	pthread_mutex_unlock(&test_lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t thread_id[200];
	t_philo	*philos;
	t_fork	*forks;
	t_rules	rules;
	struct timeval clock;
	long start_ms;
	long current_ms;

	pthread_mutex_init(&test_lock, NULL);
	pthread_create(&thread_id, NULL, test_print, NULL);
	pthread_create(&thread_id, NULL, test_print, NULL);
	pthread_join(thread_id, NULL);
// 	gettimeofday(&clock, NULL);
// 	start_ms = clock.tv_sec + (clock.tv_usec / 1000000);
// 	sleep(5);
// 	// gettimeofday(&clock, NULL);
// 	// current_ms = (clock.tv_sec + (clock.tv_usec / 1000000)) - start_ms;
// printf("clock tv_sec = %li\nclock tv_usec = %i\nstart_ms = %li\ncurrent_ms = %li\n", clock.tv_sec, clock.tv_usec, start_ms, current_ms);
// 	if (parse_input(argc, argv, &rules) < 0)
// 		return (0);
// 	philos = set_table(forks, &rules);

// printf("num_phil = %d, time_die = %d, time_eat = %d, time_sleep = %d, must_eat = %d\n",
// rules.num_phil, rules.ms_die, rules.ms_eat, rules.ms_sleep, rules.max_eat);

// 	while(philos->id != rules.num_phil)
// 	{
// 		printf("%d\n", philos->id);
// 		philos = philos->next;
// 	}
// 	printf("%d\n", philos->id);
	return (0);
}
