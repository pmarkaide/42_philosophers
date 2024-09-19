/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:19:24 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 08:57:57 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_table	*init_table(char **argv)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	table->kitchen_open = 1;
	table->n_philos = argv[1];
	table->t_die = argv[2];
	table->t_eat = argv[3];
	table->t_sleep = argv[4];
	table->n_meals = argv[5];
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
