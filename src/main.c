/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/30 15:38:14 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	eval_args(argc, argv);
	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n");
		printf("\t./philo n_philo t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (argc == 5)
		argv[5] = "0";
	table = init_table(argv);
	if (table->n_philos == 1)
		handle_one_philo(table);
	else
		handle_routine(table);
	clean_data(table);
	return (0);
}
