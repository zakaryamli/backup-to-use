/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:35:26 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 16:36:14 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static double	percent(int start, int end, int current)
{
	if (start == end)
		return (0.0);
	return ((double)(current - start) / (double)(end - start));
}

static int	color_calc(int color_a, int color_b, double percent)
{
	return (color_a + (percent * (color_b - color_a)));
}

int	get_color(int x, int y, t_der *frac, t_fdf *data)
{
	int		red;
	int		green;
	int		blue;
	double	perc;

	if (abs(frac->dx) > abs(frac->dy))
		perc = percent(data->a->x, data->b->x, x);
	else
		perc = percent(data->a->y, data->b->y, y);
	red = color_calc((data->a->color >> 16) & 255,
			(data->b->color >> 16) & 255, perc);
	green = color_calc((data->a->color >> 8) & 255,
			(data->b->color >> 8) & 255, perc);
	blue = color_calc(data->a->color & 255, data->b->color & 255, perc);
	return ((red << 16) | (green << 8) | blue);
}
