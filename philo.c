/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:09 by bsouhar           #+#    #+#             */
/*   Updated: 2023/05/28 19:08:38 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
	// t_philo *philo = (t_philo *)arg;
	printf("Test from thread\n");
	sleep(3);
	printf("Ending thread\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	data.number_of_times_each_philosopher_must_eat = -1;
	if (argc != 5 && argc != 6)
		return (1);
	data.number_of_philosophers = atoi(argv[1]);
	data.time_to_die = atoi(argv[2]);
	data.time_to_eat = atoi(argv[3]);
	data.time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data.number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	philo = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philo)
		return (1);
	while (i < data.number_of_philosophers)
	{
		pthread_mutex_init(&(philo[i].right_fork), NULL);
		philo[i].left_fork = &(philo[(i + 1)
				% data.number_of_philosophers].right_fork);
		pthread_create(&(philo[i].philo), NULL, routine, (void *)&philo[i]);
		i++;
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(philo[i].philo, NULL);
		pthread_mutex_destroy(&(philo[i].right_fork));
		i++;
	}
	free(philo);
	return (0);
}
