/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:19:24 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/21 15:35:10 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((uint64_t)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(uint64_t sleep_time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
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

int	join_threads(t_table *table)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < table->n_philos)
	{
		if (pthread_join(table->philos[i].th, NULL) != 0)
		{
			write(2, "Failed to join philosopher thread\n", 35);
			pthread_detach(table->philos[i].th);
			err = 1;
		}
		i++;
	}
	if (pthread_join(table->waiter, NULL) != 0)
	{
		write(2, "Failed to join waiter thread\n", 30);
		pthread_detach(table->waiter);
		err = 1;
	}
	return (err);
}

void	microphone(t_table *table, char *msg, int id)
{
	uint64_t	t_stamp;
	int			open;

	pthread_mutex_lock(&table->meal);
	open = table->kitchen_open;
	pthread_mutex_unlock(&table->meal);
	if (!open)
		return ;
	t_stamp = get_time() - table->t_start;
	pthread_mutex_lock(&table->microphone);
	printf("%ld %d %s\n", t_stamp, id + 1, msg);
	pthread_mutex_unlock(&table->microphone);
}
