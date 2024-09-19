/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:19:24 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/19 12:16:44 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_data(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->philos[i].fork);
		i++;
	}
	free(table->philos);
	free(table);
}

int	ft_atoi(const char *str)
{
	int			i;
	int long	nb;
	int			neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = 10 * nb + str[i++] - '0';
		if (nb < 0 && neg < 0)
			return (0);
		else if (nb < 0 && neg > 0)
			return (-1);
	}
	return (nb * neg);
}

void	lock_forks(t_philo *philo, int id)
{
	int	nb_philo;

	nb_philo = philo->table->n_philos;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->table->philos[(id + 1) % nb_philo].fork);
	}
	else
	{
		pthread_mutex_lock(&philo->table->philos[(id + 1) % nb_philo].fork);
		pthread_mutex_lock(&philo->fork);
	}
}

void	unlock_forks(t_philo *philo, int id)
{
	int	nb_philo;

	nb_philo = philo->table->n_philos;
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->philos[(id + 1) % nb_philo].fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->table->philos[(id + 1) % nb_philo].fork);
	}
}

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * 1000 + time.tv_usec / 1000);
}
