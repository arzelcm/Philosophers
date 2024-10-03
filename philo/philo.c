/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/03 17:49:37 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"
#include "vitals.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

void	join_threads(t_table *table, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < table->philos_amount)
		pthread_join(table->philos[i++].thread, NULL);
	pthread_join(*monitor, NULL);
}

static void	init_mutexs(t_table *table)
{
	pthread_mutex_init(&table->created, NULL);
	pthread_mutex_init(&table->log_mutex, NULL);
	pthread_mutex_init(&table->finished_mutex, NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitor;
	int			written;

	if (!correct_args(argc, argv))
	{
		written = write(2, "Wrong args!\n", 12);
		(void) written;
		return (EXIT_FAILURE);
	}
	init_mutexs(&table);
	pthread_mutex_lock(&table.created);
	create_table(&table, argc, argv);
	gettimeofday(&table.start_time, NULL);
	if (!table.finished && table.philos)
		printf("\n");
	pthread_mutex_unlock(&table.created);
	if (!table.philos)
		return (free(table.philos), EXIT_FAILURE);
	pthread_create(&monitor, NULL, check_simulation_routine, &table);
	join_threads(&table, &monitor);
	return (free(table.philos), EXIT_SUCCESS);
}
