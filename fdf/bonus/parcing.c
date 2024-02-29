/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:37:55 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/29 16:34:42 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	count_lines(char *filename, t_fdf *data)
{
	char	*line;
	int		fd;
	int		result;

	result = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(perror("open error"), exit(0));
	line = get_next_line(fd);
	data->width = count_words(line);
	while (line)
	{
		result++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	data->hight = result;
}

int	*set_array(char **strings, t_fdf *data, int i)
{
	int	j;
	int	*arr;
	int	k;

	arr = malloc(sizeof(int) * data->width);
	if (!arr)
		(free(strings),
			free_int_leaks(data->color_map, data->width), exit(0));
	j = 0;
	while (j < data->width)
	{
		arr[j] = ft_atoi(strings[j]);
		if (!strings[j])
			break ;
		if (ft_strchr(strings[j], ',') != 0)
		{
			k = 0;
			while (strings[j][k] != ',')
				k++;
			data->color_map[i][j] = ft_atoi_base(*(strings + j) + k + 3, 16);
		}
		j++;
	}
	free_leaks(strings);
	return (arr);
}

void	set_to_default(int **color, t_fdf *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->hight)
	{
		color[i] = malloc(sizeof(int) * data->width);
		if (!color[i])
			(perror("malloc error"), exit(1));
		j = 0;
		while (j < data->width)
		{
			color[i][j] = 0xffffff;
			j++;
		}
		i++;
	}
}

void	get_field(char *filename, t_fdf *data)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	count_lines(filename, data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(perror("open error"), exit(0));
	data->map = malloc(sizeof(int *) * data->hight);
	data->color_map = malloc(sizeof(int *) * data->hight);
	if (!data->map || !data->color_map)
		exit(1);
	set_to_default(data->color_map, data);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->map[i] = set_array(ft_split(line), data, i);
		free(line);
		i++;
	}
}
