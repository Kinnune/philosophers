/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekinnune <ekinnune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:23:53 by ekinnune          #+#    #+#             */
/*   Updated: 2023/03/30 14:52:32 by ekinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_input(int argc, char **argv, t_rules *rules)
{
	for (int i = 0; i < 3; i++)
	{
		printf("%u\n", *(((unsigned int *)rules) + i));
	}
	if (argc != 5 || argc != 6)
		return (-1);
	while (*argv)
	{
		if (**argv == '+')
			(*argv)++;
		while (**argv)
		{
			if (**argv < '0' || **argv > '9')
				return (-1);
		}
		argv++;
	}
	return (0);
}

int	main(int argv, char **argc)
{
	t_rules rules;
	rules.num_phil = 69123;
	rules.to_die = 0;
	rules.to_eat = 42;

	if (parse_input(argv, argc, &rules) < 0)
		return (0);

	return (0);
}