/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 12:16:00 by pmarkaid         ###   ########.fr       */
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
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Arguments must be positive integers\n");
				exit(1);
			}
			j++;
		}
		if (ft_atoi(argv[i]) == 0 || ft_atoi(argv[i]) == -1)
		{
			printf("Error: Integer is too big\n");
			exit(1);
		}
		i++;
	}
	return (0);
}

t_table	*init_table(char **argv)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	table->kitchen_open = 1;
	table->n_philos = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->n_meals = ft_atoi(argv[5]);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philos);
	table->t_start = get_time();
	while (i < table->n_philos)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].n_meals = 0;
		table->philos[i].t_start = table->t_start;
		table->philos[i].t_last_meal = table->t_start;
		pthread_mutex_init(&table->philos[i].fork, NULL);
		i++;
	}
	return (table);
}

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
	handle_routine(table);
	clean_data(table);
	return (0);
}
