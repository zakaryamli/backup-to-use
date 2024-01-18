/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:55:52 by zyamli            #+#    #+#             */
/*   Updated: 2024/01/18 12:04:57 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

int	check_spaces_signs(int ac, char **av)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (i < ac)
	{
		j = 0;
		k = 0;
		while (av[i][j])
			j++;
		while ((av[i][k] && av[i][k] == ' ')
		|| av[i][k] == '+' || av[i][k] == '-')
			k++;
		if (k == j)
			return (1);
		i++;
	}
	return (0);
}

int	last_check(int *arr, int j)
{
	if (check_duplicate_int(arr, j))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (j == 2 && arr[1] > arr[0])
		write(1, "sa\n", 3);
	return (0);
}

int	*set_array(char **strings)
{
	int	i;
	int	j;
	int	*arr;

	i = 0;
	while (strings[i])
		i++;
	arr = malloc(sizeof(int) * i);
	if (!arr)
		free(strings);
	j = 0;
	i -= 1;
	while (i >= 0)
	{
		arr[j] = ft_atoi(strings[i]);
		i--;
		j++;
	}
	return (arr);
}

char	**set_strings(int ac, char **av)
{
	int		i;
	char	*str;
	char	**strings;

	str = ft_strdup("");
	i = 1;
	while (i < ac)
	{
		str = ft_strjoin(str, av[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	strings = ft_split(str, ' ');
	free(str);
	return (strings);
}
