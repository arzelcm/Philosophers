/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/12 19:03:40 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include "ft_atoi.h"

int	correct_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	*philo_live(void *param)
{
	(void) param;
	printf("OKAY\n");
	return (NULL);
}

void	create_philos(int amount)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < amount)
	{
		if (pthread_create(&thread, NULL, philo_live, NULL))
			exit(2);
		printf("Creating philo\n");
		pthread_join(thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void) argv;
	if (!correct_args(argc, argv))
	{
		write(2, "Wrong args!\n", 12);
		exit(2);
	}
	create_philos(ft_atoi(argv[1]));
	return (1);
}
