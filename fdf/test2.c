/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:04:54 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/20 21:38:04 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include "fdf.h"

int find_min(int **arr, int rows, int cols) {
    
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
// int main ()
// {
// 	t_fdf data;
// 	int **a = get_field("maps/pylone.fdf", &data);
// 	printf("%d", find_max(a, data.hight,data.width));
// }