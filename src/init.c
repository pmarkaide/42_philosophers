/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:38:02 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/21 15:34:59 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->microphone, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->meal, NULL) != 0)
	{
		pthread_mutex_destroy(&table->microphone);
		return (1);
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (1);
	while (i < table->n_philos)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].n_meals = 0;
		table->philos[i].t_last_meal = get_time();
		if (pthread_mutex_init(&table->philos[i].fork, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].fork);
			free(table->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->kitchen_open = 1;
	table->n_philos = ft_atoi(argv[1]);
	table->full_philos = 0;
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->t_start = get_time();
	if (argc == 6)
		table->n_meals = ft_atoi(argv[5]);
	else
		table->n_meals = 0;
	if (init_mutex(table) || init_philos(table))
	{
		free(table);
		return (NULL);
	}
	return (table);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_create(&table->waiter, NULL, monitor, (void *)table) != 0)
	{
		write(2, "Failed to create waiter thread\n", 31);
		return (-1);
	}
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].th, NULL, routine,
				(void *)&table->philos[i]) != 0)
		{
			write(2, "Failed to create philosopher thread\n", 36);
			while (--i >= 0)
				pthread_detach(table->philos[i].th);
			pthread_detach(table->waiter);
			return (i);
		}
		i++;
	}
	return (i);
}
