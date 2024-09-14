/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:45:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/13 15:52:22 by arcanava         ###   ########.fr       */
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

typedef struct timeval	t_timeval;

struct					s_table;

typedef struct s_philo
{
	int				index;
	int				eating;
	int				thinking;
	int				sleeping;
	char			*color;
	pthread_t		thread;
	struct s_table	*table;
	struct s_philo	*prev;
	struct s_philo	*next;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				philos_amount;
	pthread_mutex_t	mutex;
	t_timeval		start_time;
}	t_table;
#endif