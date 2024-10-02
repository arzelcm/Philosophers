/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:45:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/02 13:12:17 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <sys/time.h>
# include <pthread.h>

typedef struct timeval	t_timeval;

struct					s_table;

typedef struct s_philo
{
	int				index;
	char			*color;
	int				dead;
	int				eaten_times;
	t_timeval		last_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	mutex;
	struct s_table	*table;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				philos_amount;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	int				finished;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	created;
	t_timeval		start_time;
}	t_table;

void	*create_table(t_table *table, int argc, char **argv);

#endif