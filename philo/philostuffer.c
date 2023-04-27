/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:35:31 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/27 15:44:22 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*life_of_philo(void *args)
{
	t_philo	*philo;
	t_rules	rules;

	philo = (t_philo *)args;
	rules = *(philo->rules);
	pthread_mutex_lock(&(philo->ate_mutex));
	pthread_mutex_unlock(&(philo->ate_mutex));
	if (philo->id & 1)
		ms_sleep(5);
	while (1)
	{
		get_forks(philo);
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

t_philo	*make_philo(t_rules *rules, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->rules = rules;
	philo->max_eat = rules->max_eat;
	philo->ate_at = 0;
	philo->next = NULL;
	philo->prev = NULL;
	if (pthread_mutex_init(&philo->fork, NULL)
		|| pthread_mutex_init(&philo->ate_mutex, NULL))
	{
		free(philo);
		return (NULL);
	}
	philo->right = &philo->fork;
	return (philo);
}

t_philo	*set_table(t_rules *rules)
{
	int		i;
	t_philo	*head;
	t_philo	*philos;

	philos = make_philo(rules, 1);
	if (!philos)
		return (NULL);
	head = philos;
	i = 0;
	while (i < rules->num_phil - 1)
	{
		philos->next = make_philo(rules, i + 2);
		if (!philos->next)
		{
			//free_the_list()
			return (NULL);
		}
		philos->next->prev = philos;
		philos = philos->next;
		philos->left = &philos->prev->fork;
		i++;
	}
	philos->next = head;
	head->prev = philos;
	head->left = &head->prev->fork;
	return (head);
}
