/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:46:25 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 14:47:54 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thread_mutex_error(int status, t_flag key)
{
	if (status != 0)
	{
		if (key == LOCK)
			print_error(RED"mutex lock error\n"RESET);
		if (key == UNLOCK)
			print_error(RED"mutex unlock error\n"RESET);
		if (key == INIT)
			print_error(RED"mutex init error\n"RESET);
		if (key == DESTROY)
			print_error(RED"mutex destroy error\n"RESET);
		if (key == CREATE)
			print_error(RED"pthread create error\n"RESET);
		if (key == JOIN)
			print_error(RED"pthread join error\n"RESET);
		if (key == DETACH)
			print_error(RED"pthread detach error\n"RESET);
	}
}

void thread_handler(pthread_t *thread, void *(*func)(void *), void *data, t_flag key)
{
	int	status;


	if (key == CREATE)
		status = pthread_create(thread, NULL, func, data);
	if (key == JOIN)
		status = pthread_join(*thread, NULL);
	if (key == DETACH)
		status = pthread_detach(*thread);
	thread_mutex_error(status, key);
}

void ft_mutexes(pthread_mutex_t *mutex, t_flag key)
{
	int status;
	if (key == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (key == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (key == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (key == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
	{
		print_error(RED"Wrong key num for mutexes"RESET);
		return ;
	}
	thread_mutex_error(status, key);
}