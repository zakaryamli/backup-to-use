/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keys_handler_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:59:34 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:28:05 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	destroy_win(t_fdf *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	exit(0);
}

int	mousefun(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	(void)button;
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
		data->img.ptr, 0, 0);
	return (0);
}

int	keyfun(int keycode, t_fdf *data)
{
	if (keycode == 53)
		destroy_win(data);
	zoom_translation(keycode, data);
	rotation_key(keycode, data);
	projection_key(keycode, data);
	if (keycode == 91)
		data->elavation += 0.1;
	if (keycode == 84)
		data->elavation -= 0.1;
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
		data->img.ptr, 0, 0);
	put_menu(data);
	return (0);
}
