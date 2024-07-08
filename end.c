/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:26:14 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/08 21:07:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_end(void *arg)
{
	t_table			*table;

	table = (t_table *)arg;
	while (1)
	{
		if (end_condition_reached(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	end_condition_reached(t_table *table)
{
	int	i;
	int	meal_count_reached;

	meal_count_reached = 1;
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[i]->meal_mutex);
		if (philo_is_dead(table->philos[i]))
		{
			pthread_mutex_unlock(&table->philos[i]->meal_mutex);
			return (1);
		}
		if (table->meal_count != -1)
			if (table->philos[i]->eat_count < table->meal_count)
				meal_count_reached = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_mutex);
		i++;
	}
	if (table->meal_count != -1 && meal_count_reached == 1)
	{
		pthread_mutex_lock(&table->end_mutex);
		table->end_meetup = 1;
		pthread_mutex_unlock(&table->end_mutex);
		return (1);
	}
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

void	free_data(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->end_mutex);
	i = 0;
	while (table->philos[i])
	{
		pthread_mutex_destroy(&table->philos[i]->meal_mutex);
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table);
}
