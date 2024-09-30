/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:19:24 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/30 15:42:14 by pmarkaid         ###   ########.fr       */
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

void	microphone(t_table *table, char *msg, int id)
{
	uint64_t	t_now;
	int			open;

	pthread_mutex_lock(&table->meal);
	open = table->kitchen_open;
	pthread_mutex_unlock(&table->meal);
	if (!open)
		return ;
	pthread_mutex_lock(&table->microphone);
	t_now = get_time();
	printf("%ld %d %s\n", t_now - table->t_start, id + 1, msg);
	pthread_mutex_unlock(&table->microphone);
}
