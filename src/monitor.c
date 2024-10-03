/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/03 15:19:48 by pmarkaid         ###   ########.fr       */
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

void	handle_routine(t_table *table)
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
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->philos[i].th, NULL);
		i++;
	}
	pthread_join(table->waiter, NULL);
}
