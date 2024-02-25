/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:51:02 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/25 17:35:40 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FDF_BONUS_H
# define FDF_BONUS_H
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "/usr/local/include/mlx.h"

# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1500
typedef struct s_img
{
	void *ptr;
	int lb;
	int pb;
	int endian;
	char *add;
}t_img;

typedef struct	s_cord
{
	int x;
	int y;
	int z;
	int w;
	int color;
} t_cord;

typedef struct s_fdf
{
	t_img img;
	t_cord *a;
	t_cord *b;
	int x_offset;
	int y_offset;
	int step;
	char **av;
	int hight;
	int width;
	void *mlx_ptr;
	void *mlx_window;
	int color;
	int **map;
	int **color_map;
	int x_scale;
	int y_scale;
	int z_scale;
	int tran_x;
	int tran_y;
	float zoom;
	double alpha;
	double betha;
	double gama;
	double elavation;
} t_fdf;

typedef struct s_der
{
	int dx;
	int dy;
} t_der ;

typedef struct s_color
{
	int start_color;
	int end_color;
} t_color;

long	ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int str_base);
char	**ft_split(char *str);
char	*get_next_line(int fd);
char	*ft_strchr(char *result, char c);
int	ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_join_it(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	**free_leaks(char **strs);
void	get_field(char *filename, t_fdf *data);
int		count_words(char *str);
void	free_int_leaks(int **arr,int size);
#endif