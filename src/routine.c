/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/30 15:37:08 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, int id)
{
	int	n_philo;

	n_philo = philo->table->n_philos;
	if (philo->n_meals == 0 && id % 2 != 0)
	{
		pthread_mutex_lock(&philo->table->philos[(id + 1) % n_philo].fork);
		microphone(philo->table, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->fork);
		microphone(philo->table, "has taken a fork", philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		microphone(philo->table, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->table->philos[(id + 1) % n_philo].fork);
		microphone(philo->table, "has taken a fork", philo->id);
	}
}

static void	unlock_forks(t_philo *philo, int id)
{
	int	n_philo;

	n_philo = philo->table->n_philos;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->table->philos[(id + 1) % n_philo].fork);
}

static int	eat(t_philo *philo, int t_eat)
{
	int	n_meals;

	lock_forks(philo, philo->id);
	pthread_mutex_lock(&philo->table->meal);
	philo->t_last_meal = get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->table->meal);
	microphone(philo->table, "is eating", philo->id);
	ft_usleep(t_eat);
	unlock_forks(philo, philo->id);
	if (philo->table->n_meals > 0)
	{
		pthread_mutex_lock(&philo->table->meal);
		n_meals = philo->n_meals;
		pthread_mutex_unlock(&philo->table->meal);
		if (n_meals >= philo->table->n_meals)
		{
			philo->table->full_philos++;
			return (1);
		}
	}
	return (0);
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
	int		open;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		pthread_mutex_lock(&table->meal);
		open = table->kitchen_open;
		pthread_mutex_unlock(&table->meal);
		if (!open)
			return (NULL);
		microphone(table, "is thinking", philo->id);
		if (philo->id % 2 == 0 && philo->n_meals == 0)
			ft_usleep(table->t_eat / 2);
		if (eat(philo, table->t_eat))
			break ;
		go_sleep(philo, table->t_sleep);
	}
	return (NULL);
}
