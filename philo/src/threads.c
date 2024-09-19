/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 21:48:15 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_full(t_table *table)
{
	int	i;

	i = 0;
	if(table->n_meals == 0)
		return(0);
	while (i < table->n_philos)
	{
		if (table->philos[i].n_meals < table->n_meals)
			return (0);
		i++;
	}
	return (1);
}

static void	*monitor(void *arg)
{
	int			i;
	uint64_t	t_now;
	t_table		*table;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->meal);
		if (!table->kitchen_open)
		{
			pthread_mutex_unlock(&table->meal);
			break;
		}
		pthread_mutex_unlock(&table->meal);
		i = 0;
		while (i < table->n_philos)
		{
			pthread_mutex_lock(&table->meal);
			if (all_philos_full(table))
			{
				table->kitchen_open = 0;
				pthread_mutex_unlock(&table->meal);
				break;
			}
			t_now = get_time();
			if ((t_now - table->philos[i].t_last_meal) > (uint64_t)table->t_die)
			{
				microphone(table, "died", i);
				table->kitchen_open = 0;
				pthread_mutex_unlock(&table->meal);
				return (NULL);
			}
			pthread_mutex_unlock(&table->meal);
			i++;
		}
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
