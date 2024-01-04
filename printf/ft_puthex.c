/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:45:23 by zyamli            #+#    #+#             */
/*   Updated: 2023/11/27 17:55:35 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned int a, char c, int *len)
{
	if (c == 'x')
	{
		if (a >= 16)
			ft_puthex(a / 16, c, len);
		ft_putchar("0123456789abcdef"[a % 16], len);
	}
	else if (c == 'X')
	{
		if (a >= 16)
			ft_puthex(a / 16, c, len);
		ft_putchar("0123456789ABCDEF"[a % 16], len);
	}
}
