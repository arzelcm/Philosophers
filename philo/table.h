/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:45:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/30 18:03:37 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H
# define COLORS_AMOUNT 6
# define DEF_COLOR "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PINK "\033[1;35m"
# define CYAN "\033[1;36m"

# include <sys/time.h>
# include <pthread.h>

typedef struct timeval	t_timeval;

struct					s_table;

typedef struct s_philo
{
	int				index;
	char			*color;
	int				eaten_times;
	t_timeval		last_eat;
	t_timeval		last_think;
	t_timeval		last_sleep;
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
	pthread_mutex_t	mutex;
	t_timeval		start_time;
}	t_table;

void	*create_table(t_table *table, int argc, char **argv);

#endif