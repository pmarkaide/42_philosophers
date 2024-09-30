/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/30 13:37:21 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philo_dead(t_table *table, t_philo *philo)
{
	int64_t	t_last_meal;

	pthread_mutex_lock(&table->meal);
	t_last_meal = philo->t_last_meal;
	pthread_mutex_unlock(&table->meal);
	if (get_time() - t_last_meal >= table->t_die)
		return (1);
	return (0);
}

static int	any_philo_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (is_philo_dead(table, &table->philos[i]))
		{
			pthread_mutex_lock(&table->meal);
			table->kitchen_open = 0;
			pthread_mutex_unlock(&table->meal);
			printf("%ld %d died\n", get_time() - table->t_start, i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_table	*table;
	int		full_philos;

	table = (t_table *)arg;
	while (1)
	{
		ft_usleep(1);
		if (any_philo_died(table))
			break ;
		if(table->n_meals > 0)
		{
			pthread_mutex_lock(&table->meal);
			full_philos = table->full_philos;
			pthread_mutex_unlock(&table->meal);
			if (full_philos == table->n_philos)
			{
				pthread_mutex_lock(&table->meal);
				table->kitchen_open = 0;
				pthread_mutex_unlock(&table->meal);
				break ;
			}
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
