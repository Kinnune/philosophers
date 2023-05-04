/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:35:31 by ekinnune          #+#    #+#             */
/*   Updated: 2023/05/04 15:11:32 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	*free_the_philos(t_philo *philo)
{
	t_philo	*prev;

	prev = philo->prev;
	while (philo)
	{
		free(philo);
		philo = philo->prev;
	}
	return (NULL);
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
			return (free_the_philos(philos));
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
