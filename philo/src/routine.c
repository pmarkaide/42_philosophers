/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 22:14:31 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(uint64_t sleep_time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

static void	eat(t_philo *philo, int t_eat)
{
	lock_forks(philo, philo->id);
	pthread_mutex_lock(&philo->table->meal);
	philo->t_last_meal = get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->table->meal);
	microphone(philo->table, "is eating", philo->id);
	ft_usleep(t_eat);
	unlock_forks(philo, philo->id);
}

static void	go_sleep(t_philo *philo, int t_sleep)
{
	microphone(philo->table, "is sleeping", philo->id);
	ft_usleep(t_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		if (!is_kitchen_open(table))
			break ;
		microphone(table, "is thinking", philo->id);
		eat(philo, table->t_eat);
		pthread_mutex_lock(&table->meal);
		if (table->n_meals > 0 && philo->n_meals >= table->n_meals)
		{
			pthread_mutex_unlock(&table->meal);
			break ;
		}
		pthread_mutex_unlock(&table->meal);
		go_sleep(philo, table->t_sleep);
	}
	return (NULL);
}
