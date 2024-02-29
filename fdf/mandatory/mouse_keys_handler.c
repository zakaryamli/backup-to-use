/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keys_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:39:45 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:39:54 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int destroy_win(t_fdf *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	exit(0);
}

int keyfun(int keycode, t_fdf *data)
{
	if (keycode == 53)
		destroy_win(data);
	return (0);
}