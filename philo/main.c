/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/11 11:59:58 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *make_philo(t_rules *rules, int id)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->next = NULL;
	philo->prev = NULL;
	if (pthread_mutex_init(&philo->fork, NULL));
		return (NULL);
	return (philo);
}

t_philo	*set_table(t_fork *forks, t_rules *rules)
{
	int	i;
	t_philo *head;
	t_philo *philos;

	philos = make_philo(rules, 1);
	if (!philos)
		return (NULL);
	head = philos;
	i = 0;
	while (i < rules->num_phil - 1)
	{
		philos->next = make_philo(rules, i + 2);
		if (!philos->next)
			return (NULL);
		philos->next->prev = philos;
		philos = philos->next;
		i++;
	}
	philos->next = head;
	return (head);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_fork	*forks;
	t_rules	rules;
	struct timeval clock;
	long start_ms;
	long current_ms;


	gettimeofday(&clock, NULL);
	start_ms = clock.tv_sec + (clock.tv_usec / 1000000);
	sleep(5);
	// gettimeofday(&clock, NULL);
	// current_ms = (clock.tv_sec + (clock.tv_usec / 1000000)) - start_ms;
printf("clock tv_sec = %li\nclock tv_usec = %i\nstart_ms = %li\ncurrent_ms = %li\n", clock.tv_sec, clock.tv_usec, start_ms, current_ms);
	if (parse_input(argc, argv, &rules) < 0)
		return (0);
	philos = set_table(forks, &rules);

printf("num_phil = %d, time_die = %d, time_eat = %d, time_sleep = %d, must_eat = %d\n",
rules.num_phil, rules.ms_die, rules.ms_eat, rules.ms_sleep, rules.max_eat);

	while(philos->id != rules.num_phil)
	{
		printf("%d\n", philos->id);
		philos = philos->next;
	}
	printf("%d\n", philos->id);
	return (0);
}
