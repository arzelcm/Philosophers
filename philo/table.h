/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:45:15 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/12 20:41:50 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <sys/time.h>

struct s_table;

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
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	struct timeval		startTime;
}	t_table;
#endif