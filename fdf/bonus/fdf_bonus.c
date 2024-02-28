/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:51:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/28 20:49:04 by zyamli           ###   ########.fr       */
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

void rotation_z(t_fdf *data)
{
    t_cord a = *(data->a);
    t_cord b = *(data->b);

    data->a->x = cos(data->gama) * a.x - sin(data->gama) * a.y;
    data->a->y = sin(data->gama) * a.x + cos(data->gama) * a.y;
    data->b->x = cos(data->gama) * b.x - sin(data->gama) * b.y;
    data->b->y = sin(data->gama) * b.x + cos(data->gama) * b.y;
}

double percent(int start, int end, int current)
{
	if(start == end)
		return(0.0);
	return((double)(current - start) / (double)(end - start));
}

int color_calc(int color_a, int color_b, double percent)
 {
	return(color_a + (percent * (color_b - color_a)));
 }

int get_color(int x, int y, t_der *frac, t_fdf *data)
{
	int		red;
	int		green;
	int		blue;
	double	perc;

	if (abs(frac->dx) > abs(frac->dy))
		perc = percent(data->a->x, data->b->x, x);
	else
		perc = percent(data->a->y, data->b->y, y);
	red = color_calc((data->a->color >> 16) & 255, (data->b->color >> 16) &255, perc);
	green = color_calc((data->a->color >> 8) & 255, (data->b->color >> 8) & 255, perc);
	blue = color_calc(data->a->color & 255, data->b->color & 255, perc);

	// printf("r==== %d  g==== %d b ==== %d\n", red << 16, green << 8, blue);
	return ((red << 16) | (green << 8) | blue);
}

void my_pixel_put(int x, int y, t_fdf *data, t_der *frac)
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

void	smaller_slope(t_der frac, t_fdf *data)
{
	int		p;
	t_cord	index;

	index.x = data->a->x;
	index.y = data->a->y;
	p = 2 * abs(frac.dy) - abs(frac.dx);
	point_linker_sp(data, &index, p, frac);
}
void 	isometric(t_fdf *data)
{
 int	tmp;

	tmp = data->a->x;
	data->a->x = (tmp - data->a->y) * cos(0.523599);
	data->a->y = (tmp + data->a->y) * sin(0.523599) - data->a->z;
	tmp = data->b->x;
	data->b->x = (tmp - data->b->y) * cos(0.523599);
	data->b->y = (tmp + data->b->y) * sin(0.523599) - data->b->z;
}
void draw_line(t_fdf *data)
{
	t_der	frac;

	frac.dx = data->b->x - data->a->x;
	frac.dy = data->b->y - data->a->y;
	if (abs(frac.dx) > abs(frac.dy))
		smaller_slope(frac, data);
	else
		bigger_slope(frac, data);
}

int find_max(int **arr, int rows, int cols)
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
			{
				max = arr[i][j];
			}
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
			{
				max = arr[i][j];
			}
			j++;
		}
		i++;
	}
	return (max);
}

int z_zoom(t_fdf *data)
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
		if(data->step == 0)
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

int destroy_win(t_fdf *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	exit(0);
}

int mousefun(int button, int x,int y, t_fdf *data)
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

// int hookfun(int key_hook ,t_fdf *data)
// {
// 	(void)data;
// 	printf("%d\n", key_hook);
// 	return(0);
// }
void fff()
{
	system("leaks fdf_bonus");
}
int main(int ac, char **av)
{
	t_fdf data;
	atexit(fff);
	data.zoom = 1;
	data.step = 0;
	data.tran_x = 0;
	data.tran_y = 0;
	data.elavation = 1.0;
	data.y_offset = WINDOW_HEIGHT / 2;
	data.x_offset = WINDOW_WIDTH / 2;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.mlx_window = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "my window");
	if (data.mlx_window == NULL)
	{
		free(data.mlx_window);
		return (1);
	}
	data.img.ptr = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.add = mlx_get_data_addr(data.img.ptr, &data.img.pb, &data.img.lb, &data.img.endian);
	data.av = av;
	(void)ac;
	get_field(av[1], &data);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.img.ptr, 0, 0);
	mlx_mouse_hook(data.mlx_window, &mousefun, &data);
	mlx_hook(data.mlx_window, 17, 0, &destroy_win, &data);
	mlx_hook(data.mlx_window, 2, 0, &keyfun, &data);
	put_menu(&data);
	// mlx_loop_hook(data.mlx_ptr, &hookfun, &data);
    mlx_loop(data.mlx_ptr);
}
