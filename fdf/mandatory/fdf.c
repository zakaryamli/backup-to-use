/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:45:13 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/28 16:59:49 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int end, int current)
{
	if (start == end)
		return (0.0);
	return ((double)(current - start) / (double)(end - start));
}

int	color_calc(int color_a, int color_b, double percent)
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

void	my_pixel_put(int x, int y, t_fdf *data, t_der *frac)
{
	int	pixel;
	int	*address;

	pixel = y * (data->img.lb / 4) + x;
	address = (int *)data->img.add;
	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
		address[pixel] = get_color(x, y, frac, data);
}

void	point_linker_bs(t_fdf *data, t_cord *index, int p, t_der frac)
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

void	point_linker_sp(t_fdf *data, t_cord *index, int p, t_der frac)
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

int	find_max(int **arr, int rows, int cols)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = arr[0][0];
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (arr[i][j] > max)
				max = arr[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

int	find_min(int **arr, int rows, int cols)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = arr[0][0];
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (arr[i][j] < max)
				max = arr[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

int	z_zoom(t_fdf *data)
{
	int	max;
	int	min;

	max = find_max(data->map, data->hight, data->width);
	min = find_min(data->map, data->hight, data->width);
	if (abs(max) < abs(min))
		max = min;
	if (max <= 5)
		return (5);
	else if (max <= 10)
		return (20);
	else if (max <= 30)
		return (10);
	else if (max <= 50)
		return (5);
	else if (max <= 100)
		return (2);
	else
		return (1);
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
