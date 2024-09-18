/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:30:10 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/18 20:41:45 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void go_sleep(t_philo *philo, int t_sleep)
{
    uint64_t t_now;

    t_now = get_time();
    printf("%ld %d is sleeping\n", t_now - philo->t_start, philo->id + 1);
    usleep(t_sleep * 1000);
}

static void eat(t_philo *philo, int t_eat)
{
    uint64_t t_now;
    int nb_philo;

    nb_philo = philo->table->n_philos;
    if(philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->fork);
        pthread_mutex_lock(&philo->table->philos[(philo->id + 1) % nb_philo].fork);
    }
    else
    {
        pthread_mutex_lock(&philo->table->philos[(philo->id + 1) % nb_philo].fork);
        pthread_mutex_lock(&philo->fork);
    }
    t_now = get_time();
    printf("%ld %d is eating\n", t_now - philo->t_start, philo->id + 1);
    usleep(t_eat * 1000);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&philo->table->philos[(philo->id + 1) % nb_philo].fork);
        pthread_mutex_unlock(&philo->fork);
    }
    else
    {
        pthread_mutex_unlock(&philo->fork);
        pthread_mutex_unlock(&philo->table->philos[(philo->id + 1) % nb_philo].fork);
    }
    philo->t_last_meal = get_time();
    philo->n_meals++;
}

static void think(t_philo *philo)
{
    uint64_t t_now;

    t_now = get_time();
    printf("%ld %d is thinking\n", t_now - philo->t_start, philo->id + 1);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg; 
    t_table *table = philo->table;  

    while(table->kitchen_open)
    {
        eat(philo, table->t_eat);
        if(table->n_meals > 0)
            {
                if(philo->n_meals == table->n_meals)
                break;
            }
        go_sleep(philo, table->t_sleep);
        think(philo);
    }
    return(NULL);
}
