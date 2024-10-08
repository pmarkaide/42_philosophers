/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/03 16:23:50 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	int		status;

	if (argc != 5 && argc != 6)
	{
		write(2, "Usage:\n", 7);
		write(2, "\t./philo n_philo t_die t_eat t_sleep [n_meals]\n", 47);
		return (1);
	}
	eval_args(argc, argv);
	if (argc == 5)
		argv[5] = "0";
	table = init_table(argv);
	if (!table)
	{
		clean_data(table);
		write(2, "ERROR: malloc failed\n", 21);
		return (1);
	}
	status = handle_routine(table);
	clean_data(table);
	return (status);
}
