/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:47:16 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 13:11:58 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_b(int arr[], int size)
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
	write(1, "rb\n", 3);
}

void	reverse_rotate_b(int arr[], int size)
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
	write(1, "rrb\n", 4);
}

void	push_b(int source[], int dest[], int *source_size, int *dest_size)
{
	dest[*dest_size] = source[*source_size - 1];
	(*source_size)--;
	(*dest_size)++;
	write (1, "pb\n", 3);
}

void	swap_b(int arr[], int size)
{
	int	i;

	i = arr[size - 1];
	arr[size - 1] = arr[size - 2];
	arr[size - 2] = i;
	write(1, "sb\n", 3);
}
