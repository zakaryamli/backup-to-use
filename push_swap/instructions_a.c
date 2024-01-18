/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:45:14 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 11:57:09 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(int arr[], int size)
{
	int	temp;
	int	i;

	temp = arr[size - 1];
	i = size - 1;
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = temp;
	write(1, "ra\n", 3);
}

void	reverse_rotate_a(int arr[], int size)
{
	int	temp;
	int	i;

	temp = arr[0];
	i = 0;
	while (i < size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[size - 1] = temp;
	write(1, "rra\n", 4);
}

void	push_a(int source[], int dest[], int *source_size, int *dest_size)
{
	dest[*dest_size] = source[*source_size - 1];
	(*source_size)--;
	(*dest_size)++;
	write(1, "pa\n", 3);
}

void	swap_a(int arr[], int size)
{
	int	i;

	i = arr[size -1];
	arr[size - 1] = arr[size - 2];
	arr[size - 2] = i;
	write(1, "sa\n", 3);
}
