/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:44:12 by ekinnune          #+#    #+#             */
/*   Updated: 2023/04/25 10:36:17 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	timestamp(struct timeval start_clock)
{
	struct timeval	current_clock;

	gettimeofday(&current_clock, NULL);
	current_clock.tv_sec -= start_clock.tv_sec;
	current_clock.tv_usec -= (start_clock.tv_usec + 500);
	return (timeval_to_ms(current_clock));
}

unsigned long	timeval_to_ms(struct timeval clock)
{
	return ((clock.tv_sec * 1000) + (clock.tv_usec / 1000));
}

void	mssleep(int ms)
{
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	usleep((ms * 0.8) * 1000);
	while (timestamp(clock) < ms)
		;
}
