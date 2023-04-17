/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:44:12 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/17 12:21:14 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int timestamp(struct timeval start_time)
{
	struct timeval	current_time;
	unsigned int	diff_ms = 0;

	gettimeofday(&current_time, NULL);
	current_time.tv_sec -= start_time.tv_sec;
	current_time.tv_usec -= start_time.tv_usec;
	diff_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (diff_ms);
}

unsigned long timeval_to_ms(struct timeval clock)
{
	return ((clock.tv_sec * 1000) + (clock.tv_usec / 1000));
}

// unsigned int timestamp(struct timeval start_time)
// {
// 	struct timeval	current_time;
// 	unsigned int	diff_ms = 0;

// 	gettimeofday(&current_time, NULL);
// 	current_time.tv_sec -= start_time.tv_sec;
// 	current_time.tv_usec -= start_time.tv_usec;
// 	diff_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
// 	return (diff_ms);
// }
