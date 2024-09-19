/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 16:05:01 by pmarkaid         ###   ########.fr       */
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

static void	think(t_philo *philo)
{
	microphone(philo->table, "is thinking", philo->id);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (table->kitchen_open)
	{
		if (table->kitchen_open)
			think(philo);
		eat(philo, table->t_eat);
		if (table->n_meals > 0)
		{
			if (philo->n_meals == table->n_meals)
				break ;
		}
		if (table->kitchen_open)
			go_sleep(philo, table->t_sleep);
	}
	return (NULL);
}
