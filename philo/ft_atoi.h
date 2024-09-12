/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:16:44 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/12 19:03:27 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ATOI_H
# define FT_ATOI_H

int	ft_isdigit(int c);

int	ft_atoi(const char *str);

int	ft_isnum_lim(char *str, long long max, long long min);

int	ft_isnum(char *str);

#endif