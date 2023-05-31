/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:46 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/19 12:56:10 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	{
		ms_sleep(1);
		printf("%lu %d died\n", timestamp(rules->start_clock), philo->id);
	}
}

void	*life_of_philo(void *args)
{
	t_philo	*philo;
	t_rules	rules;

	philo = (t_philo *)args;
	rules = *(philo->rules);
	pthread_mutex_lock(rules.start_mutex);
	pthread_mutex_unlock(rules.start_mutex);
	if (philo->id & 1)
		ms_sleep(5);
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&(philo->ate_mutex));
		if (philo->max_eat == 0)
			break ;
		pthread_mutex_unlock(&(philo->ate_mutex));
		printf("%lu %u is sleeping\n", timestamp(rules.start_clock), philo->id);
		ms_sleep(rules.ms_sleep);
		printf("%lu %u is thinking\n", timestamp(rules.start_clock), philo->id);
		ms_sleep(1);
	}
	pthread_mutex_unlock(&(philo->ate_mutex));
	return (NULL);
}

void	get_forks(t_philo *philo)
{
	struct timeval	start_clock;

	start_clock = philo->rules->start_clock;
	if (philo->id & 1)
	{
		pthread_mutex_lock(philo->left);
		printf("%lu %u has taken a fork\n", timestamp(start_clock), philo->id);
		pthread_mutex_lock(philo->right);
		printf("%lu %u has taken a fork\n", timestamp(start_clock), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		printf("%lu %u has taken a fork\n", timestamp(start_clock), philo->id);
		pthread_mutex_lock(philo->left);
		printf("%lu %u has taken a fork\n", timestamp(start_clock), philo->id);
	}
}

void	eat(t_philo *philo)
{
	t_rules	rules;

	rules = *(philo->rules);
	get_forks(philo);
	printf("%lu %u is eating\n", timestamp(rules.start_clock), philo->id);
	pthread_mutex_lock(&(philo->ate_mutex));
	philo->ate_at = timestamp(rules.start_clock);
	if (philo->max_eat > 0)
		philo->max_eat--;
	pthread_mutex_unlock(&(philo->ate_mutex));
	ms_sleep(rules.ms_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
