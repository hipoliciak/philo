/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meetup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:08:37 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/04 01:47:23 by dmodrzej         ###   ########.fr       */
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
		if (pthread_create(&table->philos[i]->thread, NULL, &philo_routine,
				table->philos[i]) != 0)
			return ;
		i++;
	}
	if (table->philo_count > 1)
		if (pthread_create(&table->end_thread, NULL, &check_end, table) != 0)
			return ;
	i = 0;
	while (table->philos[i])
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->end_thread, NULL);
}

void	*philo_routine(void *arg)
{
	int		first_fork;
	int		second_fork;
	t_philo	*philo;

	philo = (t_philo *)arg;
	first_fork = philo->fork[0];
	second_fork = philo->fork[1];
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(&philo->table->forks[first_fork]);
		write_status(philo, "has taken a fork");
		philo_sleep(philo->table, philo->table->time_to_die);
		write_status(philo, "is dead");
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return (NULL);
	}
	while (!has_meetup_ended(philo->table))
	{
		pthread_mutex_lock(&philo->table->forks[first_fork]);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[second_fork]);
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
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		write_status(philo, "is sleeping");
		philo_sleep(philo->table, philo->table->time_to_sleep);
		think_routine(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
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

int	philo_is_dead(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->end_meetup = 1;
		pthread_mutex_unlock(&philo->table->end_mutex);
		pthread_mutex_lock(&philo->table->write_mutex);
		printf("%ld %d is dead\n", get_time() - philo->table->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->table->write_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	has_meetup_ended(t_table *table)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&table->end_mutex);
	if (table->end_meetup == 1)
		end = 1;
	pthread_mutex_unlock(&table->end_mutex);
	return (end);
}

int	end_condition_reached(t_table *table)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (table->philos[i])
	{
		pthread_mutex_lock(&table->philos[i]->meal_mutex);
		if (philo_is_dead(table->philos[i]))
			return (1);
		if (table->meal_count != -1)
			if (table->philos[i]->eat_count < table->meal_count)
				all_ate_enough = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_mutex);
		i++;
	}
	if (table->meal_count != -1 && all_ate_enough == 1)
	{
		pthread_mutex_lock(&table->end_mutex);
		table->end_meetup = 1;
		pthread_mutex_unlock(&table->end_mutex);
		return (1);
	}
	return (0);
}

void	*check_end(void *arg)
{
	t_table			*table;

	table = (t_table *)arg;
	while (1)
	{
		if (end_condition_reached(table))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
