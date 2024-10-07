/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:28:31 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/07 15:01:31 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "vitals.h"
#include "simulation.h"

#include "utils.h"

static int	hold_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (simulation_finished(philo->table))
		return (0);
	print_vital(philo, "has taken a fork", CYAN);
	return (1);
}

int	hold_forks(t_philo *philo)
{
	if (!hold_fork(philo, &philo->prev->fork))
		return (1);
	else if (&philo->prev->fork == &philo->fork)
		return (suspend(philo->table->time_death, philo->table), 1);
	hold_fork(philo, &philo->fork);
	return (2);
}

int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i <= table->philos_amount)
	{
		if (pthread_mutex_init(&(table->philos + i)->fork, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&(table->philos + i)->mutex, NULL) != 0)
			return (0);
	}
	return (1);
}
