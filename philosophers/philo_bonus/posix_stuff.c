/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:46:25 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 16:53:10 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thread_sem_error(int status, t_flag key)
{
	if (status != 0)
	{
		if (key == WAIT)
			print_error(RED"sem wait error\n"RESET);
		if (key == POST)
			print_error(RED"sem post error\n"RESET);
		if (key == OPEN)
			print_error(RED"sem open error\n"RESET);
		if (key == CLOSE)
			print_error(RED"sem close error\n"RESET);
		if (key == UNLINK)
			print_error(RED"sem unlink error\n"RESET);
		if (key == CREATE)
			print_error(RED"pthread create error\n"RESET);
		if (key == JOIN)
			print_error(RED"pthread join error\n"RESET);
		if (key == DETACH)
			print_error(RED"pthread detach error\n"RESET);
	}
}

void	thread_handler(pthread_t *thread, void *(*func)(void *),
	void *data, t_flag key)
{
	int	status;

	if (key == CREATE)
		status = pthread_create(thread, NULL, func, data);
	if (key == JOIN)
		status = pthread_join(*thread, NULL);
	if (key == DETACH)
		status = pthread_detach(*thread);
	thread_sem_error(status, key);
}
