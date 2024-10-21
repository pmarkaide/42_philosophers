/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/21 13:31:58 by pmarkaid         ###   ########.fr       */
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
	table = init_table(argc, argv);
	if (!table)
	{
		write(2, "ERROR: initalization failed\n", 21);
		return (1);
	}
	status = handle_routine(table);
	clean_data(table);
	return (status);
}
