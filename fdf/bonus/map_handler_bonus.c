/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:51:03 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 17:38:07 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	data->a->x = (row - data->width / 2) * data->x_scale * data->zoom;
	data->a->y = (col - data->hight / 2) * data->x_scale * data->zoom;
	data->b->x = (row - data->width / 2 + 1) * data->x_scale * data->zoom;
	data->b->y = (col - data->hight / 2) * data->x_scale * data->zoom;
	data->a->z = data->map[col][row] * data->z_scale
		* data->zoom * data->elavation;
	data->a->color = data->color_map[col][row];
	if (row + 1 < data->width)
	{
		data->b->z = data->map[col][row + 1] * data->z_scale
			* data->zoom * data->elavation;
		data->b->color = data->color_map[col][row + 1];
		data->color = data->color_map[col][row];
		rotation_x(data);
		rotation_y(data);
		rotation_z(data);
		if (data->step == 0)
			isometric(data);
		data->a->x += data->x_offset + data->tran_x;
		data->a->y += data->y_offset + data->tran_y;
		data->b->x += data->x_offset + data->tran_x;
		data->b->y += data->y_offset + data->tran_y;
		draw_line(data);
	}
}

void	draw_uderline(int row, int col, t_fdf *data)
{
	data->a->x = (row - data->width / 2) * data->x_scale * data->zoom;
	data->a->y = (col - data->hight / 2) * data->x_scale * data->zoom;
	data->b->x = (row - data->width / 2) * data->x_scale * data->zoom;
	data->b->y = (col - data->hight / 2 + 1) * data->x_scale * data->zoom;
	data->a->z = data->map[col][row] * data->z_scale
		* data->zoom * data->elavation;
	if (col + 1 < data->hight)
	{
		data->b->color = data->color_map[col + 1][row];
		data->b->z = data->map[col + 1][row] * data->z_scale
			* data->zoom * data->elavation;
		data->color = data->color_map[col][row];
		rotation_x(data);
		rotation_y(data);
		rotation_z(data);
		if (data->step == 0)
			isometric(data);
		data->a->x += data->x_offset + data->tran_x;
		data->a->y += data->y_offset + data->tran_y;
		data->b->x += data->x_offset + data->tran_x;
		data->b->y += data->y_offset + data->tran_y;
		draw_line(data);
	}
}

void	set_values(t_fdf *data)
{
	data->a = (t_cord *)malloc(sizeof(t_cord));
	data->b = (t_cord *)malloc(sizeof(t_cord));
	if (!data->a || !data->b)
		exit (1);
	data->x_scale = (WINDOW_WIDTH / data->width) / 2;
	data->y_scale = (WINDOW_HEIGHT / data->hight) / 2;
	data->z_scale = z_zoom(data);
	if (data->x_scale > data->y_scale)
		data->x_scale = data->y_scale;
}

void	ft_eraser(int *add)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH)
	{
		add[i] = 0x000000;
		i++;
	}
}
