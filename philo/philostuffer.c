/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:35:31 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/17 11:11:35 by ekinnune         ###   ########.fr       */
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
	if (pthread_mutex_init(&philo->fork, NULL))
	{
		free(philo);
		return (NULL);
	}
	philo->right = &philo->fork;	
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
