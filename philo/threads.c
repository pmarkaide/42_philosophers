/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:41 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 20:51:31 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *monitor(void *arg)
{
    int i;
    uint64_t t_now;
    t_table *table = (t_table *)arg;

    while (table->kitchen_open)
    {
        i = 0;
        while (i < table->n_philos)
        {
            t_now = get_time();
            if((t_now - table->philos[i].t_last_meal) > (uint64_t)table->t_die)
            {
                table->kitchen_open = 0;
                printf("%ld %d had died\n", t_now, i + 1);
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
    return(NULL);
}

static void create_threads(t_table *table)
{
    int i;
    
    i = 0;
    pthread_create(&table->waiter, NULL, monitor, (void *)&table);
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
    pthread_join(table->waiter, NULL);
}