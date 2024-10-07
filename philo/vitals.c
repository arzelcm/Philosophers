/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vitals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:13:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/07 18:05:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vitals.h"
#include "utils.h"
#include "simulation.h"
#include <stdio.h>

void	print_vital_message(t_philo *philo, char *msg, char *color)
{
	printf("%s[%lu] %s%i%s %s\n"RESET_COLOR,
		color, get_time_now(philo->table->start_time),
		philo->color, philo->index, color, msg);
}

void	print_vital(t_philo *philo, char *msg, char *color)
{
	pthread_mutex_lock(&(philo->table->log_mutex));
	if (!simulation_finished(philo->table))
		print_vital_message(philo, msg, color);
	pthread_mutex_unlock(&(philo->table->log_mutex));
}

int	p_eat(t_philo *philo)
{
	int	holded_forks;

	holded_forks = hold_forks(philo);
	if (holded_forks == 2 && !simulation_finished(philo->table))
	{
		print_vital(philo, "is eating", BLUE);
		pthread_mutex_lock(&philo->mutex);
		philo->eaten_times++;
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->mutex);
		suspend(philo->table->time_eat, philo->table);
	}
	if (holded_forks >= 1)
		pthread_mutex_unlock(&philo->fork);
	if (holded_forks == 2)
		pthread_mutex_unlock(&philo->next->fork);
	return (1);
}

int	p_sleep(t_philo *philo)
{
	print_vital(philo, "is sleeping", GREEN);
	suspend(philo->table->time_sleep, philo->table);
	return (1);
}

int	p_think(t_philo *philo)
{
	if (!simulation_finished(philo->table))
		print_vital(philo, "is thinking", YELLOW);
	return (1);
}
