/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 14:15:27 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void go_sleep(t_philo *philo, int t_sleep)
{
    uint64_t t_now;

    t_now = get_time();
    printf("%ld %d is sleeping\n", t_now - philo->t_start, philo->id);
    usleep(t_sleep * 1000);
}

static void eat(t_philo *philo, int t_eat)
{
    uint64_t t_now;

    t_now = get_time();
    pthread_mutex_lock(&philo->fork);
    printf("%ld %d is eating\n", t_now - philo->t_start, philo->id);
    usleep(t_eat * 1000);
    pthread_mutex_unlock(&philo->fork);
}

static void think(t_philo *philo)
{
    uint64_t t_now;

    t_now = get_time();
    printf("%ld %d is thinking\n", t_now - philo->t_start, philo->id);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg; 
    t_table *table = philo->table;  

    eat(philo, table->t_eat);
    go_sleep(philo, table->t_sleep);
    think(philo);
    return(NULL);
}
