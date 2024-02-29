/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:51:02 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 21:38:55 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
#include<stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "/usr/local/include/mlx.h"

# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1500

typedef struct s_img
{
	void	*ptr;
	int		lb;
	int		pb;
	int		endian;
	char	*add;
}	t_img;

typedef struct s_cord
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_cord;

typedef struct s_fdf
{
	t_img	img;
	t_cord	*a;
	t_cord	*b;
	int		x_offset;
	int		y_offset;
	int		step;
	char	**av;
	int		hight;
	int		width;
	void	*mlx_ptr;
	void	*mlx_window;
	int		color;
	int		**map;
	int		**color_map;
	int		x_scale;
	int		y_scale;
	int		z_scale;
	int		tran_x;
	int		tran_y;
	float	zoom;
	double	alpha;
	double	betha;
	double	gama;
	double	elavation;
}	t_fdf;

typedef struct s_der
{
	int	dx;
	int	dy;
}	t_der;

long	ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int str_base);
char	**ft_split(char *str);
char	*get_next_line(int fd);
char	*ft_strchr(char *result, char c);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_join_it(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	**free_leaks(char **strs);
void	get_field(char *filename, t_fdf *data);
int		count_words(char *str);
void	free_int_leaks(int **arr, int size);
void	rotation_key(int keycode, t_fdf *data);
void	zoom_translation(int keycode, t_fdf *data);
void	projection_key(int keycode, t_fdf *data);
void	put_menu(t_fdf *data);
int		get_color(int x, int y, t_der *frac, t_fdf *data);
void	rotation_x(t_fdf *data);
void	rotation_y(t_fdf *data);
void	rotation_z(t_fdf *data);
int		z_zoom(t_fdf *data);
void	bigger_slope(t_der frac, t_fdf *data);
void	smaller_slope(t_der frac, t_fdf *data);
void	set_values(t_fdf *data);
void	draw_uderline(int row, int col, t_fdf *data);
void	draw_forline(int row, int col, t_fdf *data);
void	draw_line(t_fdf *data);
void	isometric(t_fdf *data);
int		draw_map(t_fdf *data);
int		mousefun(int button, int x, int y, t_fdf *data);
int		keyfun(int keycode, t_fdf *data);
void	ft_eraser(int *add);
int		destroy_win(t_fdf *data);
void	my_pixel_put(int x, int y, t_fdf *data, t_der *frac);
void	isometric(t_fdf *data);
#endif