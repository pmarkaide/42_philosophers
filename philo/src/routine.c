/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 14:31:54 by pmarkaid         ###   ########.fr       */
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
	uint64_t	t_now;
	int			id;

	id = philo->id;
	lock_forks(philo, id);
	t_now = get_time();
	printf("%ld %d is eating\n", t_now - philo->t_start, id + 1);
	ft_usleep(t_eat);
	unlock_forks(philo, id);
	philo->t_last_meal = get_time();
	philo->n_meals++;
}

static void	go_sleep(t_philo *philo, int t_sleep)
{
	uint64_t	t_now;

	t_now = get_time();
	printf("%ld %d is sleeping\n", t_now - philo->t_start, philo->id + 1);
	ft_usleep(t_sleep);
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
