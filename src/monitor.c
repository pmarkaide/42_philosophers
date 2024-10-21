/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/21 15:38:50 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	microphone(table, "is thinking", philo->id);
	pthread_mutex_lock(&philo->fork);
	microphone(table, "has taken a fork", philo->id);
	ft_usleep(table->t_die);
	microphone(table, "died", philo->id);
	return (NULL);
}

int	handle_one_philo(t_table *table)
{
	pthread_t	philo_thread;

	if (pthread_create(&philo_thread, NULL, one_philo,
			(void *)&table->philos[0]) != 0)
	{
		write(2, "Failed to create one philo thread\n", 34);
		return (1);
	}
	if (pthread_join(philo_thread, NULL) != 0)
	{
		write(2, "Failed to join one philo thread\n", 32);
		return (1);
	}
	return (0);
}

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

void	*monitor(void *arg)
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
