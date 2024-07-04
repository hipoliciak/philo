/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:42:21 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/04 20:43:05 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
		write_status(philo, "has taken a fork");
		philo_sleep(philo->table, philo->table->time_to_die);
		write_status(philo, "is dead");
		pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
		return (NULL);
	}
	while (!has_meetup_ended(philo->table))
	{
		pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->fork[1]]);
		write_status(philo, "has taken a fork");
		write_status(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_mutex);
		philo_sleep(philo->table, philo->table->time_to_eat);
		if (!has_meetup_ended(philo->table))
		{
			pthread_mutex_lock(&philo->meal_mutex);
			philo->eat_count++;
			pthread_mutex_unlock(&philo->meal_mutex);
		}
		pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
		pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
		write_status(philo, "is sleeping");
		philo_sleep(philo->table, philo->table->time_to_sleep);
		think_routine(philo);
	}
	return (NULL);
}

void	think_routine(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_mutex);
	time_to_think = (philo->table->time_to_die
			- (get_time() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	write_status(philo, "is thinking");
	philo_sleep(philo->table, time_to_think);
}

void	philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		if (has_meetup_ended(table))
			break ;
		usleep(100);
	}
}
