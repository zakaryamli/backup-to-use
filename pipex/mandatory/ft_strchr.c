/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:32:11 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/13 16:29:18 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;
	unsigned char	a;

	i = 0;
	str = (unsigned char *)s;
	a = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == a)
			return (1);
		i++;
	}
	return (0);
}
