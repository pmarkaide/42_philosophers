/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 09:25:25 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void eat(t_philo *philo)
{
    uint64_t t_now;

    t_now = get_time();
    pthread_mutex_lock(&philo->fork);
    printf("%ld %d is eating\n", t_now - philo->t_start, philo->id);
    pthread_mutex_unlock(&philo->fork);
}

static void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    eat(philo);
    //go_sleep(philo);
    //think(philo);  
    return(NULL);
}

static void create_threads(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->n_philos)
    {
        pthread_create(&table->philos[i].th, NULL, routine, &table->philos[i]);
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
