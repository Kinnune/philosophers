/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:08:37 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/13 11:22:45 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t lock;
	int	id;
	int	taken;
	struct s_fork	*next;
	struct s_fork	*prev;
}	t_fork;

typedef struct s_philo
{
	unsigned int id;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	// pthread_mutex_t	*left;
	// pthread_mutex_t	*right;
}	t_philo;

typedef struct s_rules
{
	unsigned int num_phil;
	unsigned int ms_die;
	unsigned int ms_eat;
	unsigned int ms_sleep;
	int max_eat;
}	t_rules;


//philostuffer.c
t_philo *make_philo(t_rules *rules, int id);
t_philo	*set_table(t_fork *forks, t_rules *rules);

//input.c
int	atoi_philo(const char *str);
int	parse_input(int argc, char **argv, t_rules *rules);


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

jokatoinen filo ottaa ensin vasemman

*/

# endif