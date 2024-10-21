/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:38:02 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/21 13:52:29 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->microphone, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->meal, NULL) != 0)
	{
		pthread_mutex_destroy(&table->microphone);
		return (1);
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (1);
	while (i < table->n_philos)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].n_meals = 0;
		table->philos[i].t_last_meal = get_time();
		if (pthread_mutex_init(&table->philos[i].fork, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].fork);
			free(table->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->kitchen_open = 1;
	table->n_philos = ft_atoi(argv[1]);
	table->full_philos = 0;
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->t_start = get_time();
	if (argc == 6)
		table->n_meals = ft_atoi(argv[5]);
	else
		table->n_meals = 0;
	if (init_mutex(table) || init_philos(table))
	{
		free(table);
		return (NULL);
	}
	return (table);
}

void	clean_data(t_table *table)
{
	int	i;

	if (!table)
		return ;
	if (table->philos)
	{
		i = 0;
		while (i < table->n_philos)
		{
			pthread_mutex_destroy(&table->philos[i].fork);
			i++;
		}
		free(table->philos);
	}
	pthread_mutex_destroy(&table->microphone);
	pthread_mutex_destroy(&table->meal);
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
