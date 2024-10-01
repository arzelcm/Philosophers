/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:57:46 by arcanava          #+#    #+#             */
/*   Updated: 2024/10/01 17:32:45 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

int	simulation_finished(t_table *table)
{
	int	finished;

	pthread_mutex_lock(&table->finished_mutex);
	finished = table->finished;
	pthread_mutex_unlock(&table->finished_mutex);
	return (finished);
}