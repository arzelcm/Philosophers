/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:57:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/30 20:17:59 by arcanava         ###   ########.fr       */
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
	pthread_mutex_lock(&(philo->table->mutex));
	printf("%s%lu %i has taken a seat\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->mutex));
	pthread_mutex_lock(&(philo->table->created));
	pthread_mutex_unlock(&(philo->table->created));
	if (philo->index % 2)
		p_eat(philo);
	else
		p_sleep(philo);
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

int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i <= table->philos_amount)
		if (pthread_mutex_init(&(table->philos + i)->fork, NULL) != 0)
			return (0);
	return (1);
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
	if (!create_philos(table, colors))
		return (table->philos = NULL, NULL);
	else
		return (table->philos);
}
