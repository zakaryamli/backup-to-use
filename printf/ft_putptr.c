/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:59:10 by zyamli            #+#    #+#             */
/*   Updated: 2023/11/27 17:56:16 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthexptr(unsigned long long a, int *len)
{
	if (a >= 16)
		ft_puthexptr(a / 16, len);
	ft_putchar("0123456789abcdef"[a % 16], len);
}

void	ft_putptr(void *i, int *len)
{
	write(1, "0x", 2);
	(*len) += 2;
	ft_puthexptr((unsigned long long)i, len);
}
