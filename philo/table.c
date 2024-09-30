/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:57:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/30 18:08:20 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
#include "ft_atoi.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void	*philo_live(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	// pthread_mutex_lock(&philo->fork);
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

t_philo	*create_philos(t_table *table)
{
	int			i;
	char		*colors[COLORS_AMOUNT];

	set_colors(colors);
	table->philos = malloc(sizeof(t_philo) * table->philos_amount);
	if (!table->philos)
		return (table->philos = NULL, NULL);
	memset(table->philos, 0, sizeof(t_philo) * table->philos_amount);
	i = 0;
	while (i < table->philos_amount)
	{
		table->philos[i].color = colors[i % COLORS_AMOUNT];
		table->philos[i].table = table;
		pthread_mutex_init(&(table->philos + i)->fork, NULL);
		table->philos[i].index = i + 1;
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_live, table->philos + i))
			return (table->philos = NULL, NULL);
		i++;
	}
	return (table->philos);
}

void	*create_table(t_table *table, int argc, char **argv)
{
	if (gettimeofday(&table->start_time, NULL) != 0)
		return (table->philos = NULL, NULL);
	table->philos_amount = ft_atoi(argv[1]);
	table->time_death = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		table->times_eat = ft_atoi(argv[5]);
	else
		table->times_eat = 0;
	if (!create_philos(table))
		return (table->philos = NULL, NULL);
	else
		return (table->philos);
}
