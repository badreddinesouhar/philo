/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:13:14 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/01 16:56:38 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_dead;
	int				nums;
	long			start;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	mutex_meals;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		philo;
	long			start;
	long			last_eat;
	int				meals;
	t_data			*data;
}					t_philo;

void				ft_print(t_philo *philo, char *msg);
void				detach(t_philo *philo, int len);
void				ft_sleep(int time);
long				ft_time(void);
void				cleanup(t_data *data, t_philo *philo,
						pthread_mutex_t *mutex);
pthread_mutex_t		*mutex_init(int len);
void				*routine(void *ph);
void				check_the_dead(t_data *data, t_philo *philo);
void				the_actual_routine(t_philo *ph);
int					error_check(const char *str, int i, int sign, long nb);
int					ft_atoi(const char *str);

#endif
