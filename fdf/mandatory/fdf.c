/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:45:13 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:44:28 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_values(t_fdf *data)
{
	data->a = malloc(sizeof(t_cord));
	data->b = malloc(sizeof(t_cord));
	if (!data->a || !data->b)
		exit (1);
	data->x_scale = (WINDOW_WIDTH / data->width) / 2;
	data->y_scale = (WINDOW_HEIGHT / data->hight) / 2;
	data->z_scale = z_zoom(data);
	if (data->x_scale > data->y_scale)
		data->x_scale = data->y_scale;
}

int	draw_map(t_fdf *data)
{
	int	row;
	int	col;

	set_values(data);
	row = 0;
	while (row < data->width)
	{
		col = 0;
		while (col < data->hight)
		{
			draw_forline(row, col, data);
			draw_uderline(row, col, data);
			col++;
		}
		row++;
	}
	free(data->a);
	free(data->b);
	return (0);
}

void fff()
{
	system("leaks fdf");
}

void create_win_img(t_fdf *data)
{
	data->mlx_window = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "my window");
	if (data->mlx_window == NULL)
	{
		free(data->mlx_window);
		exit (1);
	}
	data->img.ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.add = mlx_get_data_addr(data->img.ptr, &data->img.pb,
			&data->img.lb, &data->img.endian);
}

int	main(int ac, char **av)
{
	t_fdf	data;

	atexit(fff);
	data.y_offset = WINDOW_HEIGHT / 2;
	data.x_offset = WINDOW_WIDTH / 2;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	get_field(av[1], &data);
	create_win_img(&data);
	data.av = av;
	(void)ac;
	draw_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.img.ptr, 0, 0);
	mlx_key_hook(data.mlx_window, &keyfun, &data);
	mlx_hook(data.mlx_window, 17, 0, &destroy_win, &data);
	mlx_loop(data.mlx_ptr);
}
