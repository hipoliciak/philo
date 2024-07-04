/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meetup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:08:37 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/04 20:42:50 by dmodrzej         ###   ########.fr       */
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

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	write_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (has_meetup_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	printf("%ld %d %s\n", get_time() - philo->table->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
