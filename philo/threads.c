/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 14:16:28 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void create_threads(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->n_philos)
    {
        pthread_create(&table->philos[i].th, NULL, routine, (void *)&table->philos[i]);
        i++;
    }
}

void handle_routine(t_table *table)
{
    int i;
    create_threads(table);
    i = 0;
    while (i < table->n_philos)
    {
        pthread_join(table->philos[i].th, NULL);
        i++;
    }
}