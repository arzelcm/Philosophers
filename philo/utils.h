/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:02:34 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/02 13:23:58 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

long	get_time_now(struct timeval start);

void	suspend(int time, t_table *table);

long	get_time_now(struct timeval start);

#endif