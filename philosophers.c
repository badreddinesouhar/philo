/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:53:06 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/01 11:05:57 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = NULL;
	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_is_dead);
		if (philo->data->is_dead)
			the_actual_routine(philo);
		else
			break ;
	}
	return (NULL);
}

void	the_actual_routine(t_philo *ph)
{
	t_philo	*philo;

	philo = ph;
	pthread_mutex_unlock(&philo->data->mutex_is_dead);
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->last_eat);
	pthread_mutex_lock(&philo->data->mutex_is_dead);
	philo->last_eat = ft_time();
	philo->meals += 1;
	pthread_mutex_unlock(&philo->data->mutex_is_dead);
	pthread_mutex_unlock(&philo->data->last_eat);
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print(philo, "is sleeping");
	ft_sleep(philo->data->time_to_sleep);
	ft_print(philo, "is thinking");
}

void	cleanup(t_data *data, t_philo *philo, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(philo);
	free(mutex);
}

pthread_mutex_t	*mutex_init(int len)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * len);
	if (!mutex)
		return (NULL);
	while (i < len)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}
