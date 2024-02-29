/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:32:49 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:33:17 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_pixel_put(int x, int y, t_fdf *data, t_der *frac)
{
	int	pixel;
	int	*address;

	pixel = y * (data->img.lb / 4) + x;
	address = (int *)data->img.add;
	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
		address[pixel] = get_color(x, y, frac, data);
}

static void	point_linker_bs(t_fdf *data, t_cord *index, int p, t_der frac)
{
	int	i;

	i = 0;
	my_pixel_put(index->x, index->y, data, &frac);
	while (i < abs(frac.dy))
	{
		if (frac.dy > 0)
			index->y++;
		else
			index->y--;
		if (p < 0)
			p += 2 * abs(frac.dx);
		else
		{
			if (frac.dx > 0)
				index->x++;
			else
				index->x--;
			p += 2 * abs(frac.dx) - 2 * abs(frac.dy);
		}
		my_pixel_put(index->x, index->y, data, &frac);
		i++;
	}
}

void	bigger_slope(t_der frac, t_fdf *data)
{
	int		p;
	t_cord	index;

	index.x = data->a->x;
	index.y = data->a->y;
	p = 2 * abs(frac.dx) - abs(frac.dy);
	point_linker_bs(data, &index, p, frac);
}

static void	point_linker_sp(t_fdf *data, t_cord *index, int p, t_der frac)
{
	int	i;

	i = 0;
	my_pixel_put(data->a->x, data->a->y, data, &frac);
	while (i < abs(frac.dx))
	{
		if (frac.dx > 0)
			index->x++;
		else
			index->x--;
		if (p < 0)
			p += 2 * abs(frac.dy);
		else
		{
			if (frac.dy > 0)
				index->y++;
			else
				index->y--;
			p += 2 * abs(frac.dy) - 2 * abs(frac.dx);
		}
		my_pixel_put(index->x, index->y, data, &frac);
		i++;
	}
}

void smaller_slope(t_der frac, t_fdf *data)
{
	int		p;
	t_cord	index;

	index.x = data->a->x;
	index.y = data->a->y;
	p = 2 * abs(frac.dy) - abs(frac.dx);
	point_linker_sp(data, &index, p, frac);
}