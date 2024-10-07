/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:29:28 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/04 21:44:07 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H
# define RESET_COLOR "\033[0m"
# define RESET_COLOR_STR_LEN 4
# define RED "\033[1;31m"
# define RED_STR_LEN 7
# define GREEN "\033[1;32m"
# define GREEN_STR_LEN 7
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PINK "\033[1;35m"
# define PINK_STR_LEN 7
# define CYAN "\033[1;36m"
# define COLORS_AMOUNT 6

int		simulation_finished(t_table *table);

void	set_colors(char **colors);

void	*check_simulation_routine(void *param);

#endif