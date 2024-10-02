/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:29:02 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/02 13:15:02 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "table.h"

int		init_forks(t_table *table);

int		hold_forks(t_philo *philo);

void	*philo_live_routine(void *param);

void	*check_simulation_routine(void *param);

#endif
