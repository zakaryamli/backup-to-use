/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:10:48 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/20 14:08:26 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	int	*make_index(int arr[], int size)
{
	int	i;
	int	*result;

	result = malloc(sizeof(int) * size);
	if (!result)
		return (free(arr), NULL);
	i = 0;
	result[find_largest_number(arr, size)] = size - 1;
	while (i < size - 1)
	{
		result[find_small(arr, size)] = i;
		arr[find_small(arr, size)]
			= arr[find_largest_number(arr, size)];
		i++;
	}
	return (result);
}

static void	extract_stack_b(int *stack_a,
int *stack_b, int *size_a, int *size_b)
{
	if (*size_b == 2)
	{
		push_a(stack_b, stack_a, size_b, size_a);
		push_a(stack_b, stack_a, size_b, size_a);
		if (check_sort(stack_a, *size_a) != 0)
			swap_a(stack_a, *size_a);
	}
	else
	{
		while (*size_b > 0)
		{
			largest_two(stack_a, stack_b, size_a, size_b);
			if (check_sort(stack_a, *size_a) != 0)
				swap_a(stack_a, *size_a);
		}
	}
}

static	void	ft_sort(int stack_a[], int stack_b[], int *size_a, int *size_b)
{
	int	mid;

	sort_five(stack_a, stack_b, size_a, size_b);
	while (*size_a > 3)
	{
		mid = ((4 * stack_a[find_small(stack_a, *size_a)])
				+ stack_a[find_largest_number(stack_a, *size_a)]) / 5;
		if (stack_a[*size_a - 1] <= mid)
		{
			if (stack_a[*size_a - 1]
				<= (mid + stack_a[find_small(stack_a, *size_a)]) / 2)
			{
				push_b(stack_a, stack_b, size_a, size_b);
				rotate_b(stack_b, *size_b);
			}
			else if (stack_a[*size_a - 1]
				>= (mid + stack_a[find_small(stack_a, *size_a)]) / 2)
				push_b(stack_a, stack_b, size_a, size_b);
		}
		else
			rotate_a(stack_a, *size_a);
	}
	sort_three(stack_a, *size_a);
	extract_stack_b(stack_a, stack_b, size_a, size_b);
}

int	push_swap(int arr[], int size)
{
	int	*stack_a;
	int	*stack_b;
	int	size_b;

	size_b = 0;
	stack_b = malloc(sizeof(int) * size);
	if (!stack_b)
		return (free(arr), 0);
	stack_a = make_index(arr, size);
	free(arr);
	ft_sort(stack_a, stack_b, &size, &size_b);
	free(stack_b);
	free(stack_a);
	return (0);
}
