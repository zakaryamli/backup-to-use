/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_code_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:58:14 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/28 21:48:30 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotation_key(int keycode, t_fdf *data)
{
	if (keycode == 13)
		data->alpha += 0.05;
	if (keycode == 1)
		data->alpha -= 0.05;
	if (keycode == 0)
		data->betha += 0.05;
	if (keycode == 2)
		data->betha -= 0.05;
	if (keycode == 7)
		data->gama += 0.05;
	if (keycode == 6)
		data->gama -= 0.05;
}

void	zoom_translation(int keycode, t_fdf *data)
{
	if (keycode == 69)
		data->zoom++;
	if (keycode == 78 && data->zoom > 1)
		data->zoom--;
	if (keycode == 124)
		data->tran_x += 40;
	if (keycode == 123)
		data->tran_x -= 40;
	if (keycode == 125)
		data->tran_y += 40;
	if (keycode == 126)
		data->tran_y -= 40;
}

static void	reset_projection(int keycode, t_fdf *data)
{
	if (keycode == 34)
	{
		data->alpha = 0.0;
		data->betha = 0.0;
		data->gama = 0.0;
		data->step = 0;
	}
	if (keycode == 37)
	{
		data->alpha = 0.0;
		data->betha = 0.0;
		data->gama = 0.0;
		data->step = 1;
	}
}

void	projection_key(int keycode, t_fdf *data)
{
	if (keycode == 31)
	{
		data->alpha = 1.57;
		data->betha = 0.0;
		data->gama = 0.0;
		data->step = 1;
	}
	if (keycode == 35)
	{
		data->alpha = 0.0;
		data->betha = 1.57;
		data->gama = -1.57;
		data->step = 1;
	}
	reset_projection(keycode, data);
}

void	put_menu(t_fdf *data)
{
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 0, 0xffff,
		"Isometric view: pess 'i'");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 20,
		0xffff, "Orthographic 1: 'o'");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 40,
		0xffff, "Orthographic 2: 'p'");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 60,
		0xffff, "Orthographic 3: 'l'");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 80,
		0xffff, "flip up: 'w' flip down:'s ");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 100,
		0xffff, "flip left:'a' flip right:'d'");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 120,
		0xffff, "rotation clockwise: right:'z' left:'x'");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 140,
		0xffff, "for elavation up:'8' down:'2' ");
}
