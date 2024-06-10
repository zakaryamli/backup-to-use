/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:55:18 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/10 19:34:24 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	invalid_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0' || !str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_handler(const char *str)
{
	int			i;
	int			sign;
	long long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = tmp * 10 + (str[i] - 48);
		if (tmp > 2147483647 && sign == 1)
			return (1);
		if (tmp > 2147483648 && sign == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	check_ifvalid(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_handler(arg[i]) || invalid_str(arg[i]))
		{
			print_error(RED"Invalid Input");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parsing(t_table *table, char **av)
{
	if (check_ifvalid(&av[1]))
		return (1);
	table->philos_num = ft_atoi(av[1]);
	if (table->philos_num == 0)
		return (print_error(RED"Invalid Input"RESET), 1);
	table->time_to_die = ft_atoi(av[2]);
	if (table->time_to_die == 0)
		return (print_error(RED"Invalid Input"RESET), 1);
	table->time_to_eat = ft_atoi(av[3]);
	if (table->time_to_eat == 0)
		return (print_error(RED"Invalid Input"RESET), 1);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_sleep == 0)
		return (print_error(RED"Invalid Input"RESET), 1);
	if (av[5])
		table->meals_limit = ft_atoi(av[5]);
	else
		table->meals_limit = -1;
	return (0);
}
