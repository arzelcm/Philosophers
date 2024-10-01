/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:57:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/01 17:40:09 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
#include "philo.h"
#include "ft_atoi.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	*philo_live(void *param)
{
	t_philo	*philo;
	int		finished;
	int		(*functs[3])(t_philo *);
	int		i;

	functs[0] = p_eat;
	functs[1] = p_sleep;
	functs[2] = p_think;
	finished = 0;
	philo = (t_philo *) param;
	pthread_mutex_lock(&(philo->table->created));
	pthread_mutex_unlock(&(philo->table->created));
	i = philo->index % 2 == 0;
	while (!finished)
	{
		if (!functs[i % 3](philo))
			return (philo->table->philos = NULL, NULL);
		finished = simulation_finished(philo->table);
		i++;
	}
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

t_philo	*create_philos(t_table *table, char	**colors)
{
	int			i;

	table->philos = malloc(sizeof(t_philo) * table->philos_amount);
	if (!table->philos || !init_forks(table))
		return (table->philos = NULL, NULL);
	memset(table->philos, 0, sizeof(t_philo) * table->philos_amount);
	i = 0;
	table->philos[table->philos_amount - 1].next = table->philos;
	table->philos[0].prev = table->philos + table->philos_amount - 1;
	while (i < table->philos_amount)
	{
		table->philos[i].last_eat = table->start_time;
		if (i + 1 < table->philos_amount)
		{
			table->philos[i].next = table->philos + i + 1;
			table->philos[i].next->prev = table->philos + i;
		}
		table->philos[i].color = colors[i % COLORS_AMOUNT];
		table->philos[i].table = table;
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
	char		*colors[COLORS_AMOUNT];

	set_colors(colors);
	table->finished = 0;
	table->philos_amount = ft_atoi(argv[1]);
	table->time_death = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		table->times_eat = ft_atoi(argv[5]);
	else
		table->times_eat = 0;
	if (!create_philos(table, colors))
		return (table->philos = NULL, NULL);
	else
		return (table->philos);
}

void	*check_table_status(void *param)
{
	t_table	*table;
	int		finished;
	int		i;

	table = (t_table *) param;
	finished = 0;
	while (!finished)
	{
		i = 0;
		while (i < table->philos_amount && !finished)
		{
			pthread_mutex_lock(&table->philos[i].mutex);
			finished = get_time_now(table->philos[i].last_eat) >= table->time_death;
			pthread_mutex_unlock(&table->philos[i].mutex);
			i++;	
		}
	}
	pthread_mutex_lock(&table->log_mutex);
	printf("%s%lu %i is dead\n"DEF_COLOR,
		table->philos[i - 1].color, get_time_now(table->start_time), table->philos[i - 1].index);
	pthread_mutex_unlock(&table->log_mutex);
	pthread_mutex_lock(&table->finished_mutex);
	table->finished = 1;
	pthread_mutex_unlock(&table->finished_mutex);
	return (NULL);
}
