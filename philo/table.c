/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:57:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/03 17:47:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_atoi.h"
#include "simulation.h"
#include "vitals.h"
#include <string.h>
#include <stdlib.h>

t_philo	*create_philos(t_table *table, char	**colors)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->philos_amount);
	if (!table->philos || !init_forks(table))
		return (table->philos = NULL, NULL);
	memset(table->philos, 0, sizeof(t_philo) * table->philos_amount);
	table->philos[table->philos_amount - 1].next = table->philos;
	table->philos[0].prev = table->philos + table->philos_amount - 1;
	i = -1;
	while (++i < table->philos_amount)
	{
		gettimeofday(&table->philos[i].last_eat, NULL);
		if (i + 1 < table->philos_amount)
		{
			table->philos[i].next = table->philos + i + 1;
			table->philos[i].next->prev = table->philos + i;
		}
		table->philos[i].color = colors[i % COLORS_AMOUNT];
		table->philos[i].table = table;
		table->philos[i].index = i + 1;
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_live_routine, table->philos + i))
			return (table->philos = NULL, NULL);
	}
	return (table->philos);
}

void	*create_table(t_table *table, int argc, char **argv)
{
	char		*colors[COLORS_AMOUNT];

	set_colors(colors);
	table->philos_amount = ft_atoi(argv[1]);
	table->time_death = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->times_eat = 0;
	if (argc > 5)
		table->times_eat = ft_atoi(argv[5]);
	table->finished = table->philos_amount <= 0;
	if (table->finished || !create_philos(table, colors))
		return (table->philos = NULL, NULL);
	else
		return (table->philos);
}

void	*philo_live_routine(void *param)
{
	t_philo	*philo;
	int		finished;
	int		(*functs[VITALS_AMOUNT])(t_philo *);
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
		if (!functs[i](philo))
			return (philo->table->philos = NULL, NULL);
		finished = simulation_finished(philo->table);
		i++;
		if (i == 3)
			i = 0;
	}
	return (NULL);
}
