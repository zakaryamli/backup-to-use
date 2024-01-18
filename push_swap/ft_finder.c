/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:17:19 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 14:07:09 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_index(int stack[], int size, int element)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (stack[i] == element)
			return (i);
		i++;
	}
	return (-1);
}

int	find_small(int arr[], int size)
{
	int	min_number;
	int	min_index;
	int	i;

	if (size <= 0)
	{
		return (-1);
	}
	min_number = arr[0];
	min_index = 0;
	i = 1;
	while (i < size)
	{
		if (arr[i] < min_number)
		{
			min_number = arr[i];
			min_index = i;
		}
		i++;
	}
	return (min_index);
}

int	find_largest_number(int arr[], int size)
{
	int	max_number;
	int	max_index;
	int	i;

	if (size <= 0)
	{
		return (-1);
	}
	max_number = arr[0];
	max_index = 0;
	i = 1;
	while (i < size)
	{
		if (arr[i] > max_number)
		{
			max_number = arr[i];
			max_index = i;
		}
		i++;
	}
	return (max_index);
}

void	largest_two(int *stack_a, int *stack_b, int *size_a, int *size_b)
{
	int	largest;
	int	second_largest;

	largest = stack_b[find_largest_number(stack_b, *size_b)];
	if (steps_needed(*size_b, find_largest_number(stack_b, *size_b))
		> steps_needed(*size_b, find_index(stack_b, *size_b, largest - 1)))
	{
		if (*size_b >= 2)
		{
			second_largest
				= stack_b [find_index(stack_b, *size_b, largest - 1)];
			extract_second_largest(stack_a, stack_b, size_a, size_b);
		}
		extract_largest(stack_a, stack_b, size_a, size_b);
	}
	else
	{
		extract_largest(stack_a, stack_b, size_a, size_b);
		if (*size_b >= 2)
		{
			make_to_top_b(stack_b, *size_b,
				find_index(stack_b, *size_b, largest - 1));
			push_a(stack_b, stack_a, size_b, size_a);
		}
	}
}
