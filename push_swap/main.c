/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:38:46 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 14:29:44 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	int		i;
	int		size;
	char	**strings;
	int		*arr;

	i = 1;
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
	i = 0;
	arr = set_array(strings);
	free_leaks(strings);
	if (last_check(arr, size))
		return (0);
	push_swap(arr, size);
}
