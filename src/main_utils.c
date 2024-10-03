/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:38:02 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/10/03 16:16:20 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].n_meals = 0;
		table->philos[i].t_last_meal = get_time();
		if (pthread_mutex_init(&table->philos[i].fork, NULL) != 0)
			return (NULL);
		i++;
	}
}

t_table	*init_table(char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->kitchen_open = 1;
	table->n_philos = ft_atoi(argv[1]);
	table->n_meals = ft_atoi(argv[5]);
	table->full_philos = 0;
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->t_start = get_time();
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (NULL);
	if (!init_philos(table))
		return (NULL);
	if (pthread_mutex_init(&table->microphone, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&table->meal, NULL) != 0)
		return (NULL);
	return (table);
}

void	clean_data(t_table *table)
{
	int	i;

	if (table)
	{
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
}

int	eval_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write(2, "ERROR: arguments must be positive integers\n", 43);
				exit(1);
			}
			j++;
		}
		if (ft_atoi(argv[i]) == 0 || ft_atoi(argv[i]) == -1)
		{
			write(2, "ERROR: use a number between 1 and INT_MAX\n", 42);
			exit(1);
		}
		i++;
	}
	return (0);
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
