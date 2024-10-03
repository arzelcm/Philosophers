/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vitals.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:14:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/03 15:57:20 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VITALS_H
# define VITALS_H
# define VITALS_AMOUNT 3

# include "philo.h"

int		p_eat(t_philo *philo);

int		p_sleep(t_philo *philo);

int		p_think(t_philo *philo);

void	print_vital(t_philo *philo, char *msg, char *color);

void	print_vital_message(t_philo *philo, char *msg, char *color);

#endif
