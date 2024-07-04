/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:22 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/04 20:24:23 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meal_count = -1;
	if (argv[5])
		table->meal_count = ft_atoi(argv[5]);
	if (argv[5] && table->meal_count < 1)
	{
		free(table);
		return (NULL);
	}
	table->end_meetup = 0;
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	if (init_mutexes(table))
		return (NULL);
	return (table);
}

t_philo	**init_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (!philos)
		return (NULL);
	philos[table->philo_count] = NULL;
	while (i < table->philo_count)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		philos[i]->id = i + 1;
		philos[i]->eat_count = 0;
		philos[i]->last_meal = 0;
		philos[i]->table = table;
		assign_forks(philos[i]);
		if (pthread_mutex_init(&philos[i]->meal_mutex, NULL) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!forks)
		return (NULL);
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id - 1;
	philo->fork[1] = philo->id % philo->table->philo_count;
	if (philo->id % 2)
	{
		philo->fork[0] = philo->id % philo->table->philo_count;
		philo->fork[1] = philo->id - 1;
	}
}

int	init_mutexes(t_table *table)
{
	table->forks = init_forks(table);
	if (!table->forks)
		return (1);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->end_mutex, NULL) != 0)
		return (1);
	return (0);
}
