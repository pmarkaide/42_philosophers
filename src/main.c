/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:00:59 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/21 15:46:16 by pmarkaid         ###   ########.fr       */
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
				write(2, "ERROR: arguments must be positive integers\n", 43);
				exit(1);
			}
			j++;
		}
		if (ft_atoi(argv[i]) == 0 || ft_atoi(argv[i]) == -1)
		{
			write(2, "ERROR: use a number between 1 and INT_MAX\n", 42);
			exit(1);
		}
		i++;
	}
	return (0);
}

static void	clean_data(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->philos)
	{
		i = 0;
		while (i < table->n_philos)
		{
			pthread_mutex_destroy(&table->philos[i].fork);
			i++;
		}
		free(table->philos);
	}
	pthread_mutex_destroy(&table->microphone);
	pthread_mutex_destroy(&table->meal);
	free(table);
}

static int	handle_routine(t_table *table)
{
	int	n_threads;
	int	err;

	err = 0;
	if (table->n_philos == 1)
		return (handle_one_philo(table));
	n_threads = create_threads(table);
	if (n_threads < 0)
		return (1);
	err = join_threads(table);
	return (err);
}

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
