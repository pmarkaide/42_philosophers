/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 09:37:31 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void go_sleep(t_philo *philo)
{
    uint64_t t_now;

    t_now = get_time();
    printf("%ld %d is sleeping\n", t_now - philo->t_start, philo->id);
}

static void eat(t_philo *philo)
{
    uint64_t t_now;

    t_now = get_time();
    pthread_mutex_lock(&philo->fork);
    printf("%ld %d is eating\n", t_now - philo->t_start, philo->id);
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
    t_philo *philo;

    philo = (t_philo *)arg;
    eat(philo);
    go_sleep(philo);
    think(philo);
    return(NULL);
}
