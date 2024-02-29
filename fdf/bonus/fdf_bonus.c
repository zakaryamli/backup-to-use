/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:51:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:38:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	draw_map(t_fdf *data)
{
	int	row;
	int	col;

	ft_eraser((int *)data->img.add);
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
// void fff()
// {
// 	system("leaks fdf_bonus");
// }

void	initilizer(t_fdf *data)
{
	data->zoom = 1;
	data->step = 0;
	data->tran_x = 0;
	data->tran_y = 0;
	data->elavation = 1.0;
	data->y_offset = WINDOW_HEIGHT / 2;
	data->x_offset = WINDOW_WIDTH / 2;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		exit (1);
	data->mlx_window = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "my window");
	if (data->mlx_window == NULL)
		exit (1);
	data->img.ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img.ptr == NULL)
		exit (1);
	data->img.add = mlx_get_data_addr(data->img.ptr, &data->img.pb,
			&data->img.lb, &data->img.endian);
}

int main(int ac, char **av)
{
	t_fdf	data;

	// atexit(fff);
	if (ac != 2)
		(write(1, "input error\n", 12), exit(1));
	initilizer(&data);
	data.av = av;
	get_field(av[1], &data);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.img.ptr, 0, 0);
	mlx_mouse_hook(data.mlx_window, &mousefun, &data);
	mlx_hook(data.mlx_window, 17, 0, &destroy_win, &data);
	mlx_hook(data.mlx_window, 2, 0, &keyfun, &data);
	put_menu(&data);
	mlx_loop(data.mlx_ptr);
}
