/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:01:07 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/17 16:53:09 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>        // memset, malloc, free
# include <stdio.h>         // printf
# include <unistd.h>        // write, usleep
# include <sys/time.h>      // gettimeofday
# include <pthread.h>       // pthread functions
# include <stdint.h>        // uint64_t


typedef struct t_philo
{
    int id;
    int n_meals;
    uint64_t t_last_meal;
    pthread_t th;
    pthread_mutex_t fork;
} t_philo;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	DEAD
} t_status;

typedef struct s_table
{
    int n_philos;
    int t_die;
    int t_eat;
    int t_sleep;
    int n_meals;
    t_philo *philos;
    uint64_t t_start;    
} t_table;

/* init */
t_table *init_table(int philos, int t_die, int t_eat, int t_sleep, int n_meals);
void handle_routine(t_table *table);

#endif /* PHILO_H */