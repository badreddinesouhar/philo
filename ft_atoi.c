/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:21:14 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/01 17:57:22 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	error_check(const char *str, int i, int sign, long nb)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit(1);
		nb = (nb * 10) + (str[i] - '0');
		nb = (nb * sign);
		if (nb < INT_MIN || nb > INT_MAX)
			return (-1);
		i++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	long	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-' || str[i])
			return (-1);
		i++;
	}
	if (!str[i])
		return (-1);
	return (error_check(str, i, sign, nb));
}
