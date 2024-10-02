/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:57:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/02 13:29:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
#include "utils.h"
#include "simulation.h"
#include "vitals.h"
#include <stdio.h>

int	simulation_finished(t_table *table)
{
	int	finished;

	pthread_mutex_lock(&table->finished_mutex);
	finished = table->finished;
	pthread_mutex_unlock(&table->finished_mutex);
	return (finished);
}

void	set_colors(char **colors)
{
	colors[0] = CYAN;
	colors[1] = GREEN;
	colors[2] = YELLOW;
	colors[3] = BLUE;
	colors[4] = PINK;
	colors[5] = RED;
}

void	*check_simulation_routine(void *param)
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
			finished = get_time_now(table->philos[i].last_eat)
				>= table->time_death;
			pthread_mutex_unlock(&table->philos[i].mutex);
			i++;
		}
	}
	pthread_mutex_lock(&table->log_mutex);
	print_vital(&table->philos[i - 1], "is dead", RED);
	pthread_mutex_unlock(&table->log_mutex);
	pthread_mutex_lock(&table->finished_mutex);
	table->finished = 1;
	pthread_mutex_unlock(&table->finished_mutex);
	return (NULL);
}
