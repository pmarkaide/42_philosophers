/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 08:39:02 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n");
		printf("\t./philo n_philo t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (argc == 5)
		argv[5] = "0";
	table = init_table(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
			atoi(argv[4]), atoi(argv[5]));
	handle_routine(table);
	return (0);
}
