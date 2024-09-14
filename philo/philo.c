/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/13 15:54:47 by arcanava         ###   ########.fr       */
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
#include <pthread.h>
#include <unistd.h>

long	get_time_now(struct timeval start)
{
	struct timeval	now;

	(void) start;
	if (gettimeofday(&now, NULL) != 0)
		return (-1);
	return (((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}

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

	philo = (t_philo *) param;
	// pthread_mutex_lock(&philo->mutex);
	// pthread_mutex_lock(&(philo->table->mutex));
	printf("%s%lu %i has taken a seat\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	return (NULL);
}

void	set_colors(char **colors)
{
	colors[0] = RED;
	colors[1] = GREEN;
	colors[2] = YELLOW;
	colors[3] = BLUE;
	colors[4] = PINK;
	colors[5] = CYAN;
}

void	*create_philos(int amount, t_table *table)
{
	int			i;
	char		*colors[COLORS_AMOUNT];	

	set_colors(colors);
	if (gettimeofday(&table->start_time, NULL) != 0)
		return (table->philos = NULL, NULL);
	table->philos_amount = amount;
	table->philos = malloc(sizeof(t_philo) * amount);
	if (!table->philos)
		return (table->philos = NULL, NULL);
	memset(table->philos, 0, sizeof(t_philo) * amount);
	i = 0;
	while (i < amount)
	{
		table->philos[i].color = colors[i % COLORS_AMOUNT];
		table->philos[i].table = table;
		pthread_mutex_init(&(table->philos + i)->mutex, NULL);
		table->philos[i].index = i + 1;
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_live, table->philos + i))
			return (table->philos = NULL, NULL);
		i++;
	}
	return (table->philos);
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
	t_table	table;

	if (!correct_args(argc, argv))
		return (write(2, "Wrong args!\n", 12), EXIT_FAILURE);
	create_philos(ft_atoi(argv[1]), &table);
	if (!table.philos)
		return (free(table.philos), EXIT_FAILURE);
	else
		join_threads(&table);
	return (free(table.philos), EXIT_SUCCESS);
}
