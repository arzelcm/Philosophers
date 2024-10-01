/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:00:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/01 18:02:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	get_time(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	suspend(int time)
{
	int	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
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

int	p_eat(t_philo *philo)
{
	int	holded_forks;

	holded_forks = hold_forks(philo);
	if (!simulation_finished(philo->table))
	{
		print_vital(philo, "is eating");
		pthread_mutex_lock(&philo->mutex);
		philo->eaten_times++;
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->mutex);
		suspend(philo->table->time_eat);
	}
	if (holded_forks >= 1)
		pthread_mutex_unlock(&philo->fork);
	if (holded_forks == 2)
		pthread_mutex_unlock(&philo->prev->fork);
	return (1);
}

int	p_sleep(t_philo *philo)
{
	print_vital(philo, "is sleeping");
	suspend(philo->table->time_sleep);
	return (1);
}

int	p_think(t_philo *philo)
{
	if (!simulation_finished(philo->table))
		print_vital(philo, "is thinking");
	return (1);
}
