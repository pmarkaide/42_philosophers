/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:19:24 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 14:09:34 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

uint64_t get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (uint64_t)time.tv_sec * 1000 + time.tv_usec / 1000;
}

t_table *init_table(int philos, int t_die, int t_eat, int t_sleep, int n_meals)
{
    t_table *table;
    int i;

    i = 0;
    table = (t_table *)malloc(sizeof(t_table));
    table->n_philos = philos;
    table->t_die = t_die;
    table->t_eat = t_eat;
    table->t_sleep = t_sleep;
    table->n_meals = n_meals;
    table->philos = (t_philo *)malloc(sizeof(t_philo) * philos);
    table->t_start = get_time();
    while (i < philos)
    {
        table->philos[i].id = i;
        table->philos[i].table = table;
        table->philos[i].n_meals = 0;
        table->philos[i].t_start = table->t_start;
        table->philos[i].t_last_meal = table->t_start;
        pthread_mutex_init(&table->philos[i].fork, NULL);
        i++;
    }
    return (table);
}
