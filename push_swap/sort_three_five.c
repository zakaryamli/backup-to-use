/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:32:08 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 14:13:27 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(int *arr, int size)
{
	if (size == 3)
	{
		if (arr[2] > arr[1] && arr[1] < arr[0] && arr[0] > arr[2])
			swap_a(arr, size);
		else if (arr[2] > arr[1] && arr[1] > arr[0] && arr[0] < arr[2])
		{
			swap_a(arr, size);
			reverse_rotate_a(arr, size);
		}
		else if (arr[2] > arr[1] && arr[1] < arr[0] && arr[0] < arr[2])
			rotate_a(arr, size);
		else if (arr[2] < arr[1] && arr[1] > arr[0] && arr[0] > arr[2])
		{
			swap_a(arr, size);
			rotate_a(arr, size);
		}
		else if (arr[2] < arr[1] && arr[1] > arr[0] && arr[0] < arr[2])
			reverse_rotate_a(arr, size);
	}
}

void	sort_five(int *stack_a, int *stack_b, int *size_a, int *size_b)
{
	int	smallest;

	if (*size_a == 5)
	{
		smallest = stack_a[find_small(stack_a, *size_a)];
		if (steps_needed(*size_a, find_small(stack_a, *size_a))
			< steps_needed(*size_a, find_index(stack_a, *size_a,
					stack_a[find_small(stack_a, *size_a)] + 1)))
		{
			make_to_top_a(stack_a, *size_a, find_small(stack_a, *size_a));
			push_b(stack_a, stack_b, size_a, size_b);
			make_to_top_a(stack_a, *size_a,
				find_index(stack_a, *size_a, smallest + 1));
			push_b(stack_a, stack_b, size_a, size_b);
		}
		else
		{
			make_to_top_a(stack_a, *size_a, find_index(stack_a, *size_a,
					stack_a[find_small(stack_a, *size_a)] + 1));
			push_b(stack_a, stack_b, size_a, size_b);
			make_to_top_a(stack_a, *size_a, find_small(stack_a, *size_a));
			push_b(stack_a, stack_b, size_a, size_b);
		}
	}
}
