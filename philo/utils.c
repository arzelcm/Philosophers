/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:00:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/03 15:56:10 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include <unistd.h>

int	get_time(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	suspend(int time, t_table *table)
{
	int	start_time;

	start_time = get_time();
	while (get_time() - start_time < time && !simulation_finished(table))
		usleep(100);
}

long	get_time_now(struct timeval start)
{
	struct timeval	now;

	(void) start;
	gettimeofday(&now, NULL);
	return (((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}
