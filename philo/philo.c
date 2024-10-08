/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/07 18:51:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"
#include "vitals.h"
#include "simulation.h"
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

void	set_starting_time(t_table *table)
{
	int	i;

	i = 0;
	gettimeofday(&table->start_time, NULL);
	while (i < table->philos_amount)
		table->philos[i++].last_eat = table->start_time;
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitor;
	int			written;

	if (!correct_args(argc, argv))
	{
		written = write(STDERR_FILENO, RED"Wrong args!\n"RESET_COLOR,
				12 + RED_STR_LEN + RESET_COLOR_STR_LEN);
		(void) written;
		return (EXIT_FAILURE);
	}
	init_mutexs(&table);
	pthread_mutex_lock(&table.created);
	if (!create_table(&table, argc, argv))
		return (EXIT_FAILURE);
	if (!table.finished && table.philos)
		printf("\n");
	set_starting_time(&table);
	pthread_mutex_unlock(&table.created);
	if (!table.philos)
		return (free(table.philos), EXIT_FAILURE);
	pthread_create(&monitor, NULL, check_simulation_routine, &table);
	join_threads(&table, &monitor);
	return (free(table.philos), EXIT_SUCCESS);
}
