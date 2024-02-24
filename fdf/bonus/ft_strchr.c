/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:22:47 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/23 17:55:03 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

char	*ft_strchr(char *result, char c)
{
	int	i;

	i = 0;
	while (result[i] != '\0')
	{
		if (result[i] == c)
			return (&result[i]);
		i++;
	}
	return (0);
}