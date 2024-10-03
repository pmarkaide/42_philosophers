/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/03 16:24:14 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philo_dead(t_table *table, t_philo *philo)
{
	int64_t	t_last_meal;

	pthread_mutex_lock(&table->meal);
	if (philo->table->n_meals > 0 && philo->n_meals >= philo->table->n_meals)
	{
		pthread_mutex_unlock(&table->meal);
		return (0);
	}
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
			pthread_mutex_lock(&table->microphone);
			printf("%ld %d died\n", get_time() - table->t_start, i + 1);
			pthread_mutex_unlock(&table->microphone);
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
		ft_usleep(5);
		if (any_philo_died(table))
			break ;
		if (table->n_meals > 0)
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

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_create(&table->waiter, NULL, monitor, (void *)table) != 0)
	{
		write(2, "Failed to create waiter thread\n", 31);
		return (1);
	}
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].th, NULL, routine,
				(void *)&table->philos[i]) != 0)
		{
			write(2, "Failed to create philosopher thread\n", 36);
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_routine(t_table *table)
{
	int	i;

	if (table->n_philos == 1)
		return (handle_one_philo(table));
	i = 0;
	if (create_threads(table))
		return (1);
	while (i < table->n_philos)
	{
		if (pthread_join(table->philos[i].th, NULL) != 0)
		{
			write(2, "Failed to join philosopher thread\n", 35);
			return (1);
		}
		i++;
	}
	if (pthread_join(table->waiter, NULL) != 0)
	{
		write(2, "Failed to join waiter thread\n", 30);
		return (1);
	}
	return (0);
}
