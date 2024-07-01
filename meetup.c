/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meetup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:08:37 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/01 22:55:41 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_meetup(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (table->philos[i])
	{
		if (pthread_create(&table->philos[i]->thread, NULL, philo_routine,
				table->philos[i]) != 0)
			return ;
		i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;
    int	first_fork = philo->fork[0];
    int	second_fork = philo->fork[1];

	pthread_mutex_lock(&table->forks[first_fork]);
	pthread_mutex_lock(&table->forks[second_fork]);

	pthread_mutex_lock(&philo->table->write_mutex);
	printf("Philo %d has taken forks number %d and %d\n", philo->id, first_fork, second_fork);
	pthread_mutex_unlock(&philo->table->write_mutex);

	pthread_mutex_lock(&philo->table->write_mutex);
	printf("Philo %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);

	pthread_mutex_lock(&philo->table->write_mutex);
	printf("Philo %d has put down forks number %d and %d\n", philo->id, first_fork, second_fork);
	pthread_mutex_unlock(&philo->table->write_mutex);

	pthread_mutex_unlock(&table->forks[first_fork]);
	pthread_mutex_unlock(&table->forks[second_fork]);
	return NULL;
}

// void	philo_sleep(t_table *table, time_t sleep_time)
// {
// 	time_t	wake_up;

// 	wake_up = get_time_in_ms() + sleep_time;
// 	while (get_time_in_ms() < wake_up)
// 	{
// 		if (has_simulation_stopped(table))
// 			break ;
// 		usleep(100);
// 	}
// }

// int	philo_is_dead(t_philo *philo)
// {
// 	if (get_time() - philo->last_meal > 800)
// 	{
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("Philo %d is dead\n", philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		pthread_mutex_lock(philo->right_fork);
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("Philo %d is eating\n", philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);
// 		philo->last_meal = get_time();
// 		philo->eat_count++;
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("Philo %d is sleeping\n", philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);
// 		usleep(1000);
// 		pthread_mutex_lock(philo->print_mutex);
// 		printf("Philo %d is thinking\n", philo->id);
// 		pthread_mutex_unlock(philo->print_mutex);
// 	}
// 	return (NULL);
// }
