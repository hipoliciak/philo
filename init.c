/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:07:22 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/06/30 21:40:05 by dmodrzej         ###   ########.fr       */
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
	table->start_time = get_time();
	table->dead = 0;
	table->philos = init_philos(table);
	if (!table->philos)
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
		philos[i]->last_meal = table->start_time;
		philos[i]->table = table;
		i++;
	}
	return (philos);
}

void	free_data(t_table *table)
{
	int	i;

	i = 0;
	while (table->philos[i])
	{
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table);
}
