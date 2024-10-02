/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/02 13:26:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_atoi.h"
#include "table.h"
#include "vitals.h"

int	correct_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_amount)
		pthread_join(table->philos[i++].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitor;

	if (!correct_args(argc, argv))
		return (write(2, "Wrong args!\n", 12), EXIT_FAILURE);
	pthread_mutex_init(&table.created, NULL);
	pthread_mutex_init(&table.log_mutex, NULL);
	pthread_mutex_init(&table.finished_mutex, NULL);
	pthread_mutex_lock(&table.created);
	create_table(&table, argc, argv);
	gettimeofday(&table.start_time, NULL);
	pthread_mutex_unlock(&table.created);
	if (!table.philos)
		return (free(table.philos), EXIT_FAILURE);
	pthread_create(&monitor, NULL, check_simulation_routine, &table);
	pthread_join(monitor, NULL);
	join_threads(&table);
	return (free(table.philos), EXIT_SUCCESS);
}
