/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:51:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/24 22:24:22 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf_bonus.h"

//  float **orthogonal(float left,float right,float bottom,float top,float near,float far)
//     {
//         float **matrix = malloc(sizeof(float *) * 4);
// 		matrix[0] = malloc(sizeof(float) * 4);
// 		matrix[1] = malloc(sizeof(float) * 4);
// 		matrix[2] = malloc(sizeof(float) * 4);
// 		matrix[3] = malloc(sizeof(float) * 4);
// 		matrix[0] = (float[]){1, 0, 0, 0};
// 		matrix[1] = (float[]){0, 1, 0, 0};
// 		matrix[2] = (float[]){0, 0, 1, 0};
// 		matrix[3] = (float[]){0, 0, 0, 1};
		
//         matrix[0][0] = 2/(right - left);
//        matrix[1][1] = 2/(top - bottom);
//        matrix[2][2] = -2/(far - near);
//        matrix[3][2] = (far+near)/(far - near);
//        matrix[3][0] = (right+left)/(right -left);
//        matrix[3][1] = (top + bottom)/(top-bottom);

//        return matrix;
// }

// t_fdf  matrix_multiply(float ** M, t_fdf v) 
// {
//    t_fdf result = v;
   
//     result.a->x = M[0][0]*v.a->x + M[0][1]*v.a->y + M[0][2]*v.a->z + M[0][3]*v.a->w;
//     result.a->y= M[1][0]*v.a->x + M[1][1]*v.a->y + M[1][2]*v.a->z + M[1][3]*v.a->w;
//     result.a->z = M[2][0]*v.a->x + M[2][1]*v.a->y + M[2][2]*v.a->z + M[2][3]*v.a->w;
//     result.a->w = M[3][0]*v.a->x + M[3][1]*v.a->y + M[3][2]*v.a->z + M[3][3]*v.a->w;
    
// 	result.b->x = M[0][0]*v.b->x + M[0][1]*v.b->y + M[0][2]*v.b->z + M[0][3]*v.b->w;
//     result.b->y= M[1][0]*v.b->x + M[1][1]*v.b->y + M[1][2]*v.b->z + M[1][3]*v.b->w;
//     result.b->z = M[2][0]*v.b->x + M[2][1]*v.b->y + M[2][2]*v.b->z + M[2][3]*v.b->w;
//     result.b->w = M[3][0]*v.b->x + M[3][1]*v.b->y + M[3][2]*v.b->z + M[3][3]*v.b->w;
    
// 	return result;
// }

void rotation_x(t_fdf *data)
{
    t_cord a = *(data->a);
    t_cord b = *(data->b);

    data->a->y = cos(data->alpha) * a.y - sin(data->alpha) * a.z;
    data->a->z = sin(data->alpha) * a.y + cos(data->alpha) * a.z;
    data->b->y = cos(data->alpha) * b.y - sin(data->alpha) * b.z;
    data->b->z = sin(data->alpha) * b.y + cos(data->alpha) * b.z;
}

void rotation_y(t_fdf *data)
{
    t_cord a = *(data->a);
    t_cord b = *(data->b);

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
	int red;
	int green;
	int blue;
	double perc;

	if(frac->dx > frac->dy)
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
	int pixel;
	int *address;

	pixel = y * (data->img.lb / 4) + x;
	address = (int *)data->img.add;
	// printf("%x\n", data->color);
	// printf("%d %d\n", x, y);
	if(x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
		address[pixel] = get_color(x, y, frac, data);
}
void point_linker_bs(t_fdf *data, t_cord *index, int p, t_der frac)
{
	int i;

	i = 0;
	my_pixel_put(index->x, index->y, data, &frac);
	while(i < abs(frac.dy))
	{
		if(frac.dy > 0)
			index->y++;
		else
			index->y--;
		if(p < 0)
			p += 2 * abs(frac.dx);
		else
		{
			if(frac.dx > 0)
				index->x++;
			else
				index->x--;
			p += 2 * abs(frac.dx) - 2 * abs(frac.dy);
		}
		my_pixel_put(index->x, index->y, data, &frac);
		i++;
	}
}
void bigger_slope(t_der frac, t_fdf *data)
{
	int p;

	t_cord index;
	index.x = data->a->x;
	index.y = data->a->y;
	p = 2 * abs(frac.dx) - abs(frac.dy);
	point_linker_bs(data, &index, p, frac);
}

void point_linker_sp(t_fdf *data, t_cord *index, int p, t_der frac)
{
	int i;

	i = 0;
	my_pixel_put(data->a->x, data->a->y, data, &frac);
	while (i < abs(frac.dx))
	{
		if(frac.dx > 0)
			index->x++;
		else
			index->x--;
		if(p < 0)
			p += 2 * abs(frac.dy);
		else
		{
			if(frac.dy > 0)
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
	int p;

	t_cord index;
	index.x = data->a->x;
	index.y = data->a->y;

	p = 2 * abs(frac.dy) - abs(frac.dx);
	point_linker_sp(data, &index, p, frac);
}
void  isometric(t_fdf *data)
{
 int tmp;

 tmp = data->a->x;
 data->a->x = (tmp - data->a->y) * cos(0.523599);
 data->a->y = (tmp + data->a->y) * sin(0.523599) - data->a->z;
 tmp = data->b->x;
 data->b->x = (tmp - data->b->y) * cos(0.523599);
 data->b->y = (tmp + data->b->y) * sin(0.523599) - data->b->z;
}
void draw_line(t_fdf *data)
{
	t_der frac;
	frac.dx = data->b->x - data->a->x;
	frac.dy = data->b->y - data->a->y;
	if(abs(frac.dx) > abs(frac.dy))
	{
		smaller_slope(frac, data);
	}
	else
	{
		bigger_slope(frac, data);
	}

	
}
// int f(int key, t_fdf *fdf)
// {
// 	(void)fdf;
// 	printf("%d\n", key);
// 	if (key == 124)
// 		fdf->x_offset += 10;
// 	else if (key == 123)
// 		fdf->y_offset += 10;
// 	draw(fdf);
// 	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_window, fdf->img.ptr, 0, 0);

// 	return (0);
// }
int find_max(int **arr, int rows, int cols)
{
    
	int i = 0;
	int j = 0;
	int max;
	max = arr[0][0];
    while (i < rows) {
        j = 0;
        while (j < cols) {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
            j++;
        }
        i++;
    }

    return max;
}
int find_min(int **arr, int rows, int cols)
{
    
	int i = 0;
	int j = 0;
	int max;
	max = arr[0][0];
    while (i < rows) 
	{
        j = 0;
        while (j < cols) {
            if (arr[i][j] < max) {
                max = arr[i][j];
            }
            j++;
        }
        i++;
    }
    return max;
}

int z_zoom(t_fdf *data)
{
	int max;
	int min;
	max = find_max(data->map, data->hight, data->width);
	min = find_min(data->map, data->hight, data->width);
	if(abs(max) < abs(min))
		max = min;
	if(max <= 5)
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
void draw_forline(int row, int col, t_fdf *data)
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
		if(data->step == 0)
			isometric(data);
		data->a->x += data->x_offset + data->tran_x;
		data->a->y += data->y_offset + data->tran_y;
		data->b->x += data->x_offset + data->tran_x;
		data->b->y += data->y_offset + data->tran_y;
		draw_line(data);
		}
}
void draw_uderline(int row, int col, t_fdf *data)
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
void set_values(t_fdf *data)
{
	data->a = malloc(sizeof(t_cord));
	data->b = malloc(sizeof(t_cord));

	data->x_scale = (WINDOW_WIDTH / data->width) / 2;
	data->y_scale =  (WINDOW_HEIGHT / data->hight) / 2;
	data->z_scale = z_zoom(data);
	if(data->x_scale > data->y_scale)
		data->x_scale = data->y_scale;
}
int draw_map(t_fdf *data)
{
	int row;
	int col;
	int  i = 0;
	int *add = (int *)data->img.add;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH)
	{
		add[i] = 0x000000;
		i++;
	}
	set_values(data);
	row = 0;
	while(row < data->width)
	{
		col = 0;
		while(col < data->hight)
		{
			draw_forline(row, col, data);
			// printf("\t(%d, %d) = (%d, %d)\n", row- data->width / 2, col - data->hight / 2, row- data->width / 2, col + 1 - data->hight / 2);
			draw_uderline(row, col, data);
			col++;
		}
		row++;
	}
	return 0;
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
	// printf("zoom%f\n", data->zoom);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->img.ptr, 0,0);
	return(0);
}

int keyfun(int keycode, t_fdf *data)
{
	if(keycode == 53)
		destroy_win(data);
	if(keycode == 69)
		data->zoom++;
	if(keycode == 78 && data->zoom > 1)
		data->zoom--;
	if(keycode == 124)
		data->tran_x += 40;
	if(keycode == 123)
		data->tran_x -= 40;
	if(keycode == 125)
		data->tran_y += 40;
	if(keycode == 126)
		data->tran_y -= 40;
	if(keycode == 13)
		data->alpha += 0.05;
	if(keycode == 1)
		data->alpha -= 0.05;
	if(keycode == 0)
		data->betha += 0.05;
	if(keycode == 2)
		data->betha -= 0.05;
	if(keycode == 7)
		data->gama += 0.05;
	if(keycode == 6)
		data->gama -= 0.05;
	if(keycode == 31)
	{
		data->alpha = 1.57;
		data->betha = 0.0;
		data->gama = 0.0;
		data->step = 1;
	}
	if(keycode == 35)
	{
		data->alpha = 0.0;
		data->betha = 1.57;
		data->gama = -1.57;
		data->step = 1;
	}
	if(keycode == 34)
	{
		data->alpha = 0.0;
		data->betha = 0.0;
		data->gama = 0.0;
		data->step = 0;
	}
	if(keycode == 37)
	{
		data->alpha = 0.0;
		data->betha = 0.0;
		data->gama = 0.0;
		data->step = 1;
	}
	if(keycode == 91)
		data->elavation += 0.1;
	if(keycode == 84)
		data->elavation -= 0.1;
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->img.ptr, 0,0);
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 0, 0xffff, "Isometric view: pess 'i'\nOrthographic 1: 'o'\n");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 40,
		 0xffff, "Orthographic 2: 'p'\nOrthographic 3: 'l'\nfor rotation up: 'w' down:'s' flip left:'a' flip right:'d' right:'z' left:'x'\n ");
	mlx_string_put(data->mlx_ptr, data->mlx_window, 0, 60,
		 0xffff,"\n for elavation; '8' '2' ");
	 
	
	// if(button == 5)
	printf("%d\n", keycode);
		
	return(0);
}

// int hookfun(int key_hook ,t_fdf *data)
// {
// 	(void)data;
// 	printf("%d\n", key_hook);
// 	return(0);
// }

int main(int ac, char **av)
{
	t_fdf data;
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
    data.mlx_window = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,"my window");
    if (data.mlx_window == NULL)
    {
        free(data.mlx_window);
        return (1);
    }
	data.img.ptr = mlx_new_image(data.mlx_ptr ,WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.add = mlx_get_data_addr(data.img.ptr, &data.img.pb, &data.img.lb, &data.img.endian);
	data.av = av;
	(void)ac;
	get_field(av[1], &data);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.img.ptr, 0,0);
	mlx_mouse_hook(data.mlx_window, &mousefun, &data);
	mlx_hook(data.mlx_window, 17, 0, &destroy_win, &data);
	mlx_hook(data.mlx_window, 2, 0, &keyfun, &data);
	mlx_string_put(data.mlx_ptr, data.mlx_window, 0, 0, 0xffff, "Isometric view: pess 'i'\nOrthographic 1: 'o'\n");
	mlx_string_put(data.mlx_ptr, data.mlx_window, 0, 40,
		 0xffff, "Orthographic 2: 'p'\nOrthographic 3: 'l'\nfor rotation up: 'w' down:'s' flip left:'a' flip right:'d' right:'z' left:'x'\n");
	mlx_string_put(data.mlx_ptr, data.mlx_window, 0, 60,
		 0xffff,"\n for elavation; '8' '2' ");
	// mlx_loop_hook(data.mlx_ptr, &hookfun, &data);
    mlx_loop(data.mlx_ptr);
    free(data.mlx_ptr);
}
