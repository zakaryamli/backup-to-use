/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_protection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:01:29 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 14:18:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	check_overflow(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_handler(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static	int	invalid_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0' || !str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	check_invalid(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (invalid_str(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_protection(char **arg)
{
	if (check_duplicate(arg) || check_invalid(arg) || check_overflow(arg))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
