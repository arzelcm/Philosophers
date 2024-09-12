/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/12 20:41:57 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include "ft_atoi.h"
#include "table.h"

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

void	*philo_live(void *param)
{
	t_philo	*philo;

	philo = param;
	printf("[%i] Philo living(%lu)\neating: %i, thinking: %i, sleeping: %i, color: %s\n\n",
			philo->index, philo->thread, philo->eating, philo->thinking, philo->sleeping, philo->color);
	return (NULL);
}

t_philo	*create_philos(int amount, t_table *table)
{
	int			i;

	gettimeofday(&table->startTime, NULL);
	table->philos = malloc(sizeof(t_philo) * amount);
	if (!table->philos)
		return(NULL);
	memset(table->philos, 0, sizeof(t_philo) * amount);
	i = 0;
	while (i < amount)
	{
		table->philos[i].index = i + 1;
		if (pthread_create(&table->philos[i].thread, NULL, philo_live, table->philos + i))
			return(NULL);
		printf("Creating philo\n");
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!correct_args(argc, argv))
		return (write(2, "Wrong args!\n", 12), EXIT_FAILURE);
	create_philos(ft_atoi(argv[1]), &table);
	if (!table.philos)
		return (free(table.philos), EXIT_FAILURE);
	return (free(table.philos), EXIT_SUCCESS);
}
