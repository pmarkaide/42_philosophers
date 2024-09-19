/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 08:55:22 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eval_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error: Arguments must be positive integers\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		args[6];

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
	handle_routine(table);
	return (0);
}
