/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:38:46 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/20 14:03:43 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	int		size;
	char	**strings;
	int		*arr;

	if (check_spaces_signs(ac, av))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	size = 0;
	strings = set_strings(ac, av);
	if (ft_protection(strings))
		return (0);
	while (strings[size])
		++size;
	arr = set_array(strings);
	free_leaks(strings);
	if (last_check(arr, size))
		return (0);
	if (check_sort(arr, size))
		push_swap(arr, size);
	return (0);
}
