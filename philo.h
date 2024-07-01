/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:29:29 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/01 22:56:46 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int				philo_count;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meal_count;
	time_t			start_time;
	int				dead;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}				t_table;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			eat_count;
	time_t		last_meal;
	int			fork[2];
	t_table		*table;
}				t_philo;

// args.c
int				check_number_of_args(int argc);
int				check_args_values(char **argv);

// init.c
t_table			*init_table(char **argv);
t_philo			**init_philos(t_table *table);
pthread_mutex_t	*init_forks(t_table *table);
void			assign_forks(t_philo *philo);
int				init_mutexes(t_table *table);

// meetup.c
void			start_meetup(t_table *table);
void			*philo_routine(void *arg);

// utils.c
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
time_t			get_time(void);
void			free_data(t_table *table);

#endif