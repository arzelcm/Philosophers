/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:00:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/30 19:55:25 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long	get_time_now(struct timeval start)
{
	struct timeval	now;

	(void) start;
	if (gettimeofday(&now, NULL) != 0)
		return (-1);
	return (((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}

int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&(philo->prev->fork));
	pthread_mutex_lock(&(philo->table->mutex));
	printf("%s%lu %i is eating\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->mutex));
	if (gettimeofday(&philo->last_eat, NULL) != 0)
		return (0);
	usleep(philo->table->time_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	return (1);
}

int	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->mutex));
	printf("%s%lu %i is sleeping\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->mutex));
	if (gettimeofday(&philo->last_sleep, NULL) != 0)
		return (0);
	usleep(philo->table->time_sleep);
	return (1);
}
