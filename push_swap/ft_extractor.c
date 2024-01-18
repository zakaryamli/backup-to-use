/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extractor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:21:09 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 13:42:05 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	steps_needed(int size, int index)
{
	int	k;
	int	steps;

	k = ((index) > (size) / 2);
	steps = (size * (k)) + (1 - 2 * (k)) * (index) + 1 *(!(k));
	return (steps);
}

void	make_to_top_b(int *stack, int size, int index)
{
	int	i;

	i = steps_needed(size, index);
	if (index > (size / 2))
	{
		while (i -1 > 0)
		{
			rotate_b(stack, size);
			i--;
		}
	}
	else if (index <= (size / 2))
	{
		while (i > 0)
		{
			reverse_rotate_b(stack, size);
			i--;
		}
	}
}

void	make_to_top_a(int *stack, int size, int index)
{
	int	i;

	i = steps_needed(size, index);
	if (index > (size / 2))
	{
		while (i -1 > 0)
		{
			rotate_a(stack, size);
			i--;
		}
	}
	else if (index <= (size / 2))
	{
		while (i > 0)
		{
			reverse_rotate_a(stack, size);
			i--;
		}
	}
}

void	extract_largest(int *stack_a, int *stack_b, int *size_a, int *size_b)
{
	make_to_top_b(stack_b, *size_b, find_largest_number(stack_b, *size_b));
	push_a(stack_b, stack_a, size_b, size_a);
}

void	extract_second_largest(int *stack_a, int *stack_b,
	int *size_a, int *size_b)
{
	int	largest;

	largest = stack_b[find_largest_number(stack_b, *size_b)];
	make_to_top_b(stack_b, *size_b, find_index(stack_b, *size_b, largest - 1));
	push_a(stack_b, stack_a, size_b, size_a);
}
