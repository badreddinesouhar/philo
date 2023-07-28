/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:43:40 by bsouhar           #+#    #+#             */
/*   Updated: 2023/07/28 05:07:28 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (philo->data->is_dead)
		printf("%ld %d %s\n", ft_time() - philo->data->start, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	detach(t_philo *philo, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_detach(philo[i].philo);
		i++;
	}
}

long	ft_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}

void	ft_sleep(int time)
{
	long	i;

	i = ft_time() + time;
	while (ft_time() < i)
		usleep(200);
}
