/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/20 15:29:51 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_full(t_table *table)
{
	int	i;

	if (table->n_meals == 0)
		return (0);
	pthread_mutex_lock(&table->meal);
	i = 0;
	while (i < table->n_philos)
	{
		if (table->philos[i].n_meals < table->n_meals)
		{
			pthread_mutex_unlock(&table->meal);
			return (0);
		}
		i++;
	}
	table->kitchen_open = 0;
	pthread_mutex_unlock(&table->meal);
	return (1);
}

static int	philo_is_dead(t_table *table)
{
	int			i;
	uint64_t	t_now;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_lock(&table->meal);
		t_now = get_time();
		if ((t_now - table->philos[i].t_last_meal) > (uint64_t)table->t_die)
		{
			pthread_mutex_unlock(&table->meal);
			microphone(table, "died", i);
			pthread_mutex_lock(&table->meal);
			table->kitchen_open = 0;
			pthread_mutex_unlock(&table->meal);
			return (1);
		}
		pthread_mutex_unlock(&table->meal);
		i++;
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (philo_is_dead(table))
			break ;
		if (all_philos_full(table))
			break ;
		if (is_kitchen_open(table))
			break ;
	}
	return (NULL);
}

static void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	pthread_create(&table->waiter, NULL, monitor, (void *)table);
	while (i < table->n_philos)
	{
		pthread_create(&table->philos[i].th, NULL, routine,
			(void *)&table->philos[i]);
		i++;
	}
}

void	handle_routine(t_table *table)
{
	int	i;

	create_threads(table);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->philos[i].th, NULL);
		i++;
	}
	pthread_join(table->waiter, NULL);
}
