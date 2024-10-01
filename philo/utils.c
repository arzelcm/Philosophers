/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:00:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/01 15:11:15 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
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

// TODO: If finished don't eat!!
int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&(philo->table->log_mutex));
	printf("%s%lu %i has taken a fork\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->log_mutex));
	pthread_mutex_lock(&philo->prev->fork);
	pthread_mutex_lock(&(philo->table->log_mutex));
	printf("%s%lu %i has taken a fork\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->log_mutex));
	pthread_mutex_lock(&(philo->table->log_mutex));
	printf("%s%lu %i is eating\n"DEF_COLOR,
		philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->log_mutex));
	philo->eaten_times++;
	gettimeofday(&philo->last_eat, NULL);
	suspend(philo->table->time_eat);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
	return (1);
}

int	p_sleep(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&(philo->table->log_mutex));
	pthread_mutex_lock(&philo->table->finished_mutex);
	finished = philo->table->finished;
	pthread_mutex_unlock(&philo->table->finished_mutex);
	if (!finished)
		printf("%s%lu %i is sleeping\n"DEF_COLOR,
			philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->log_mutex));
	suspend(philo->table->time_sleep);
	return (1);
}

int	p_think(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&(philo->table->log_mutex));
	pthread_mutex_lock(&philo->table->finished_mutex);
	finished = philo->table->finished;
	pthread_mutex_unlock(&philo->table->finished_mutex);
	if (!finished)
		printf("%s%lu %i is thinking\n"DEF_COLOR,
			philo->color, get_time_now(philo->table->start_time), philo->index);
	pthread_mutex_unlock(&(philo->table->log_mutex));
	return (1);
}
