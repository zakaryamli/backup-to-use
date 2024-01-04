/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:44:47 by zyamli            #+#    #+#             */
/*   Updated: 2023/11/26 16:58:13 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_toascii(int nb, int *len)
{
	char	str[10];
	int		i;

	i = 0;
	while (nb > 0)
	{
		str[i] = nb % 10 + 48;
		nb = nb / 10;
		i++;
	}
	while (i--)
	{
		write(1, &str[i], 1);
		(*len)++;
	}
}

void	ft_putnbr(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		(*len)++;
		n = -n;
		ft_toascii(n, len);
	}
	else if (n == 0)
	{
		write(1, "0", 1);
		(*len)++;
	}
	else
		ft_toascii(n, len);
}
