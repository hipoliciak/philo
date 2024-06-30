/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:37:28 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/06/26 20:20:24 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal > 800)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("Philo %d is dead\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		return (1);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("Philo %d is eating\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		philo->last_meal = get_time();
		philo->eat_count++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("Philo %d is sleeping\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		usleep(1000);
		pthread_mutex_lock(philo->print_mutex);
		printf("Philo %d is thinking\n", philo->id);
		pthread_mutex_unlock(philo->print_mutex);
	}
	return (NULL);
}
