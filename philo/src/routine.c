/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 09:55:01 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo, int t_eat)
{
	uint64_t	t_now;
	int			id;

	id = philo->id;
	lock_forks(philo, id);
	t_now = get_time();
	printf("%ld %d is eating\n", t_now - philo->t_start, id + 1);
	usleep(t_eat * 1000);
	unlock_forks(philo, id);
	philo->t_last_meal = get_time();
	philo->n_meals++;
}

static void	go_sleep(t_philo *philo, int t_sleep)
{
	uint64_t	t_now;

	t_now = get_time();
	printf("%ld %d is sleeping\n", t_now - philo->t_start, philo->id + 1);
	usleep(t_sleep * 1000);
}

static void	think(t_philo *philo)
{
	uint64_t	t_now;

	t_now = get_time();
	printf("%ld %d is thinking\n", t_now - philo->t_start, philo->id + 1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (table->kitchen_open)
	{
		eat(philo, table->t_eat);
		if (table->n_meals > 0)
		{
			if (philo->n_meals == table->n_meals)
				break ;
		}
		if (table->kitchen_open)
			go_sleep(philo, table->t_sleep);
		if (table->kitchen_open)
			think(philo);
	}
	return (NULL);
}
