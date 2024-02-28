/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:17:27 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/28 16:58:59 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_check(char c, int base)
{
	char	*maxbase;
	char	*maxbase2;

	maxbase = "0123456789abcdef";
	maxbase2 = "0123456789ABCDEF";
	while (base--)
		if (maxbase[base] == c || maxbase2[base] == c)
			return (1);
	return (0);
}

int	ft_turner(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;

	result = 0;
	if (*str == '-')
		sign = -1;
	else
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_check(*str, str_base))
		result = result * str_base + ft_turner(*str++);
	return (result * sign);
}
