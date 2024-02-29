/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:37:12 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:38:48 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotation_x(t_fdf *data)
{
	t_cord	a;
	t_cord	b;

	a = *(data->a);
	b = *(data->b);
	data->a->y = cos(data->alpha) * a.y - sin(data->alpha) * a.z;
	data->a->z = sin(data->alpha) * a.y + cos(data->alpha) * a.z;
	data->b->y = cos(data->alpha) * b.y - sin(data->alpha) * b.z;
	data->b->z = sin(data->alpha) * b.y + cos(data->alpha) * b.z;
}

void	rotation_y(t_fdf *data)
{
	t_cord	a;
	t_cord	b;

	a = *(data->a);
	b = *(data->b);
	data->a->x = cos(data->betha) * a.x + sin(data->betha) * a.z;
	data->a->z = -sin(data->betha) * a.x + cos(data->betha) * a.z;
	data->b->x = cos(data->betha) * b.x + sin(data->betha) * b.z;
	data->b->z = -sin(data->betha) * b.x + cos(data->betha) * b.z;
}

void	rotation_z(t_fdf *data)
{
	t_cord	a;
	t_cord	b;

	a = *(data->a);
	b = *(data->b);
	data->a->x = cos(data->gama) * a.x - sin(data->gama) * a.y;
	data->a->y = sin(data->gama) * a.x + cos(data->gama) * a.y;
	data->b->x = cos(data->gama) * b.x - sin(data->gama) * b.y;
	data->b->y = sin(data->gama) * b.x + cos(data->gama) * b.y;
}
void	isometric(t_fdf *data)
{
	int	tmp;

	tmp = data->a->x;
	data->a->x = (tmp - data->a->y) * cos(0.523599);
	data->a->y = (tmp + data->a->y) * sin(0.523599) - data->a->z;
	tmp = data->b->x;
	data->b->x = (tmp - data->b->y) * cos(0.523599);
	data->b->y = (tmp + data->b->y) * sin(0.523599) - data->b->z;
}
