/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:34:58 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:35:26 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	find_max(int **arr, int rows, int cols)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = arr[0][0];
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (arr[i][j] > max)
				max = arr[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

static int	find_min(int **arr, int rows, int cols)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = arr[0][0];
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (arr[i][j] < max)
				max = arr[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

int	z_zoom(t_fdf *data)
{
	int	max;
	int	min;

	max = find_max(data->map, data->hight, data->width);
	min = find_min(data->map, data->hight, data->width);
	if (abs(max) < abs(min))
		max = min;
	if (max <= 5)
		return (5);
	else if (max <= 10)
		return (20);
	else if (max <= 30)
		return (10);
	else if (max <= 50)
		return (5);
	else if (max <= 100)
		return (2);
	else
		return (1);
}
