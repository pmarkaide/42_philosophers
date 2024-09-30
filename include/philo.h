/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:01:07 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/09/30 15:39:04 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // pthread functions
# include <stdint.h>   // uint64_t
# include <stdio.h>    // printf
# include <stdlib.h>   // memset, malloc, free
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep

typedef struct s_table	t_table;
typedef struct t_philo
{
	int					id;
	int					n_meals;
	t_table				*table;
	uint64_t			t_last_meal;
	pthread_t			th;
	pthread_mutex_t		fork;
}						t_philo;
typedef struct s_table
{
	int					kitchen_open;
	int					n_philos;
	int					n_meals;
	int					full_philos;
	uint64_t			t_die;
	uint64_t			t_eat;
	uint64_t			t_sleep;
	pthread_t			waiter;
	pthread_mutex_t		microphone;
	pthread_mutex_t		meal;
	t_philo				*philos;
	uint64_t			t_start;
}						t_table;

uint64_t				get_time(void);
t_table					*init_table(char **argv);
int						eval_args(int argc, char **argv);
void					clean_data(t_table *table);
int						ft_atoi(const char *str);
void					*routine(void *arg);
void					handle_routine(t_table *table);
void					microphone(t_table *table, char *msg, int id);
void					handle_one_philo(t_table *table);
void					ft_usleep(uint64_t sleep_time);

#endif /* PHILO_H */
