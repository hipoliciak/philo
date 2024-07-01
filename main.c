/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:28:15 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/01 21:25:43 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (check_number_of_args(argc))
		return (1);
	if (check_args_values(argv))
		return (1);
	table = init_table(argv);
	if (!table)
		return (1);
	start_meetup(table);
	free_data(table);
	return (0);
}
