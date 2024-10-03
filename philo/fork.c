/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:28:31 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "vitals.h"
#include "simulation.h"

int	hold_forks(t_philo *philo)
{
	if (philo->index % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		if (simulation_finished(philo->table))
			return (1);
		print_vital(philo, "has taken a fork", CYAN);
		pthread_mutex_lock(&philo->prev->fork);
		if (simulation_finished(philo->table))
			return (2);
		print_vital(philo, "has taken a fork", CYAN);
		return (2);
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		if (simulation_finished(philo->table))
			return (1);
		print_vital(philo, "has taken a fork", CYAN);
		pthread_mutex_lock(&philo->fork);
		if (simulation_finished(philo->table))
			return (2);
		print_vital(philo, "has taken a fork", CYAN);
		return (2);
	}
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
