/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:11:23 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/20 14:01:56 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_duplicate_int(int arr[], int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int	check_duplicate(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL)
	{
		j = i + 1;
		while (str[j] != NULL)
		{
			if (!ft_strcmp(str[i], str[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_sort(int arr[], int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (arr[i] > arr[i - 1])
			return (1);
		i++;
	}
	return (0);
}
