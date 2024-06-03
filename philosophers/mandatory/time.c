/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:57:35 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/28 13:30:06 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL))
		print_error(RED"gettimeofday error"RESET);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void ft_usleep(int miliseconds, t_table *table)
{
	size_t	start;

	start = get_time();
	while(get_time() - start < miliseconds && !action_done(table))
		usleep(1);
}