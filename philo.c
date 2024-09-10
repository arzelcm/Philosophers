/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:46:47 by arcanava          #+#    #+#             */
/*   Updated: 2024/09/10 18:01:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void	*philo_live(void *param)
{
	(void) param;
	printf("OKAY\n");
	return (NULL);
}

void	create_philos(int amount)
{
	int				i;
	pthread_t	thread;

	i = 0;
	while (i < amount)
	{
		if (pthread_create(&thread, NULL, philo_live, NULL))
			exit(2);
		printf("Creating philo\n");
		pthread_detach(thread);
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void) argv;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong args\n", 11);
		exit(2);
	}
	create_philos(atoi(argv[1]));
	return (1);
}
