/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:08:37 by ekinnune          #+#    #+#             */
/*   Updated: 2023/03/30 14:28:55 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_fork
{
	int id;
	int taken;
}	t_fork;

typedef struct s_philo
{
	unsigned int id;
}	t_philo;

typedef struct s_rules
{
	unsigned int num_phil;
	unsigned int to_die;
	unsigned int to_eat;
	unsigned int to_sleep;
}	t_rules;

/*
external functions

	memset
	printf
	malloc
	free
	write
	usleep
	gettimeofday
	pthread_create
	pthread_detach
	pthread_join
	pthread_mutex_init
	pthread_mutex_destroy
	pthread_mutex_lock
	pthread_mutex_unlock
*/

# endif