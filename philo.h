/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:29:29 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/06/30 21:41:33 by dmodrzej         ###   ########.fr       */
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
	int		philo_count;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		meal_count;
	time_t	start_time;
	int		dead;
	t_philo	**philos;
}				t_table;

typedef struct s_philo
{
	// pthread_t	thread;
	int			id;
	int			eat_count;
	time_t		last_meal;
	t_table		*table;
}				t_philo;

int		check_number_of_args(int argc);
int		check_args_values(char **argv);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
t_table	*init_table(char **argv);
time_t	get_time(void);
t_philo	**init_philos(t_table *table);
void	free_data(t_table *table);
void	*philo_routine(void *arg);

#endif