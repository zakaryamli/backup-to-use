/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:47:02 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 16:26:21 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freez_threads(t_philo *philo)
{
	bool 	i;

	i = false;
	while(1)
	{
		ft_mutexes(&philo->table->table_lock, LOCK);
		i = philo->table->all_in;
		ft_mutexes(&philo->table->table_lock, UNLOCK);
		if (i == true)
			break ;
	}
	if(philo->count % 2 != 0)
		ft_usleep(philo->table->time_to_eat, philo->table);
	
}

static int	ft_handler(const char *str, int sign)
{
	int			i;
	long long	handler;
	long long	tmp;

	i = 0;
	handler = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = handler * 10 + (str[i] - 48); 
		if (tmp < handler && sign == 1)
			return (-1);
		if (tmp < handler && sign == -1)
			return (0);
		handler = tmp;
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_handler(&str[i], sign) == -1)
		return (-1);
	if (ft_handler(&str[i], sign) == 0)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void	print_error(char *err)
{
	while(*err)
		write(2, err++, 1);
}