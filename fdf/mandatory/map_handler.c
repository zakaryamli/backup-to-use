/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:36:34 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:40:56 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void  isometric(t_fdf *data)
{
	int	tmp;

	tmp = data->a->x;
	data->a->x = (tmp - data->a->y) * cos(0.523599);
	data->a->y = (tmp + data->a->y) * sin(0.523599) - data->a->z;
	tmp = data->b->x;
	data->b->x = (tmp - data->b->y) * cos(0.523599);
	data->b->y = (tmp + data->b->y) * sin(0.523599) - data->b->z;
}

void	draw_line(t_fdf *data)
{
	t_der	frac;

	frac.dx = data->b->x - data->a->x;
	frac.dy = data->b->y - data->a->y;
	if (abs(frac.dx) > abs(frac.dy))
		smaller_slope(frac, data);
	else
		bigger_slope(frac, data);
}

void	draw_forline(int row, int col, t_fdf *data)
{
	data->a->x = (row - data->width / 2) * data->x_scale;
	data->a->y = (col - data->hight / 2) * data->x_scale;
	data->b->x = (row - data->width / 2 + 1) * data->x_scale;
	data->b->y = (col - data->hight / 2) * data->x_scale;
	data->a->z = data->map[col][row] * data->z_scale;
	data->a->color = data->color_map[col][row];
	if (row + 1 < data->width)
	{
		data->b->z = data->map[col][row + 1] * data->z_scale ;
		data->b->color = data->color_map[col][row + 1];
		isometric(data);
		data->a->x += data->x_offset;
		data->a->y += data->y_offset;
		data->b->x += data->x_offset;
		data->b->y += data->y_offset;
		draw_line(data);
	}
}

void draw_uderline(int row, int col, t_fdf *data)
{
	data->a->x = (row - data->width / 2) * data->x_scale;
	data->a->y = (col - data->hight / 2) * data->x_scale;
	data->b->x = (row - data->width / 2) * data->x_scale;
	data->b->y = (col - data->hight / 2 + 1) * data->x_scale;
	data->a->z = data->map[col][row] * data->z_scale;
	if (col + 1 < data->hight)
	{
		data->b->color = data->color_map[col + 1][row];
		data->b->z = data->map[col + 1][row] * data->z_scale;
		data->color = data->color_map[col][row];
		isometric(data);
		data->a->x += data->x_offset;
		data->a->y += data->y_offset;
		data->b->x += data->x_offset;
		data->b->y += data->y_offset;
		draw_line(data);
	}
}