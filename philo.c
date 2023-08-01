/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:09 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/01 18:02:53 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return ;
	if (ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1
		|| ft_atoi(argv[3]) == -1 || ft_atoi(argv[4]) == -1)
		return ;
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0 || ft_atoi(argv[3]) == 0
		|| ft_atoi(argv[4]) == 0)
		return ;
	if (argc == 6 && (ft_atoi(argv[5]) == -1 || ft_atoi(argv[5]) == 0))
		return ;
	data->nums = -1;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start = ft_time();
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->last_eat, NULL);
	data->is_dead = 1;
	pthread_mutex_init(&data->mutex_is_dead, NULL);
	pthread_mutex_init(&data->mutex_meals, NULL);
	if (argc == 6)
		data->nums = ft_atoi(argv[5]);
}

void	run_philosophers(t_data *data, t_philo *philo, pthread_mutex_t *mutex)
{
	int		i;
	long	time;

	i = 0;
	time = ft_time();
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].meals = -1;
		philo[i].data = data;
		philo[i].right_fork = &mutex[i];
		philo[i].left_fork = &(mutex[(i + 1) % data->number_of_philosophers]);
		philo[i].start = time;
		philo[i].last_eat = time;
		pthread_create(&(philo[i].philo), NULL, routine, (void *)&philo[i]);
		i++;
	}
	check_the_dead(data, philo);
	cleanup(data, philo, mutex);
}

int	is_philo_dead(t_philo *philo, int i, int nums)
{
	if ((ft_time() - philo[i].last_eat) > philo[i].data->time_to_die)
	{
		printf("%ld %d is dead\n", ft_time() - philo[i].start, philo[i].id);
		return (1);
	}
	if (nums != -1)
	{
		if (philo[i].meals >= nums)
		{
			return (1);
		}
	}
	return (0);
}

void	check_the_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (data->is_dead)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->mutex_is_dead);
			if (is_philo_dead(philo, i, data->nums))
			{
				data->is_dead = 0;
				detach(philo, data->number_of_philosophers);
				pthread_mutex_unlock(&data->mutex_is_dead);
				return ;
			}
			pthread_mutex_unlock(&data->mutex_is_dead);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*mutex;

	data = malloc(sizeof(data));
	initialize_data(data, argc, argv);
	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (1);
	mutex = mutex_init(data->number_of_philosophers);
	run_philosophers(data, philo, mutex);
	return (0);
}
