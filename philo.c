/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:09 by bsouhar           #+#    #+#             */
/*   Updated: 2023/07/28 04:57:36 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *data, int argc, char **argv)
{
	data->number_of_times_each_philosopher_must_eat = -1;
	if (argc != 5 && argc != 6)
		return ;
	// data->eat = 0;
	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->start = ft_time();
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->last_eat, NULL);
	data->is_dead = 1;
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
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
	while (data->is_dead)
    {
        i = 0;
        while (i < data->number_of_philosophers)
        {
			pthread_mutex_lock(&data->last_eat);
            if ((ft_time() - philo[i].last_eat) >= philo[i].data->time_to_die)
            {
                printf("%ld %d is dead\n", ft_time() - philo[i].start,
                        philo[i].id);
                data->is_dead = 0;
                detach(philo, data->number_of_philosophers);
                break ;
            }
			pthread_mutex_unlock(&data->last_eat);
            if (data->number_of_times_each_philosopher_must_eat != -1)
            {
                if (philo[i].meals >= data->number_of_times_each_philosopher_must_eat)
                {
                    data->is_dead = 0;
                    detach(philo, data->number_of_philosophers);
                    break ;
                }
            }
        }
    }
	cleanup(data, philo, mutex);
}

int main(int argc, char **argv)
{
		t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*mutex;

	initialize_data(&data, argc, argv);
	philo = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!philo)
		return (1);
	mutex = mutex_init(data.number_of_philosophers);
	run_philosophers(&data, philo, mutex);
	return (0);
}
