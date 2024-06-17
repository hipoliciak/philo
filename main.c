/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:28:15 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/06/17 19:32:08 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].last_meal = 0;
		philos[i].left_fork = malloc(sizeof(pthread_mutex_t));
		philos[i].right_fork = malloc(sizeof(pthread_mutex_t));
		philos[i].print_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i].left_fork, NULL);
		pthread_mutex_init(philos[i].right_fork, NULL);
		pthread_mutex_init(philos[i].print_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(philos[i].left_fork);
		pthread_mutex_destroy(philos[i].right_fork);
		pthread_mutex_destroy(philos[i].print_mutex);
		free(philos[i].left_fork);
		free(philos[i].right_fork);
		free(philos[i].print_mutex);
		i++;
	}
	free(philos);
	return (0);
}
