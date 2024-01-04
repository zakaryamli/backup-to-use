/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:57:11 by zyamli            #+#    #+#             */
/*   Updated: 2023/11/27 18:05:26 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_toascii(unsigned int nb, int *len)
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

void	ft_putunsigned(unsigned int n, int *len)
{
	if (n == 0)
	{
		write (1, "0", 1);
		(*len)++;
	}
	else
		ft_toascii(n, len);
}
