#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 600

void my_pixel_put(int x, int y, t_fdf *data)
{
	int pixel;
	int *address;

	pixel = y * (data->img.lb / 4) + x;
	address = (int *)data->img.add;
	// printf("%x\n", data->color);
	if(x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
		address[pixel] = data->color;
}
void draw_line(t_fdf *data) {
    int x0 = data->a->x;
    int y0 = data->a->y;
    int x1 = data->b->x;
    int y1 = data->b->y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_pixel_put(x0, y0, data);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int main() 
{
	t_fdf data;
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
	int *pixel = (int *)data.img.add;
	// y = WINDOW_HEIGHT / 2;
	// x = WINDOW_WIDTH / 2;
	data.color =  0xffffff;
t_cord a = { .x = 0, .y = 600 };
t_cord b = { .x = 600, .y = 0 };
	data.a = &a;
	data.b = &b;

    draw_line(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_window, data.img.ptr, 0,0);
    mlx_loop(data.mlx_ptr);
    free(data.mlx_ptr);

    return 0;
}
