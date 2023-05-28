/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:14 by bsouhar           #+#    #+#             */
/*   Updated: 2023/05/26 19:44:26 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "lib/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_data;

typedef struct s_philo
{
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		philo;
}					t_philo;

#endif