/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:46:25 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/02 14:34:20 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void thread_sem_error(int status, t_flag key)
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

void thread_handler(pthread_t *thread, void *(*func)(void *), void *data, t_flag key)
{
	int	status;

	if (key == CREATE)
		status = pthread_create(thread, NULL, func, data);
	else if (key == JOIN)
		status = pthread_join(*thread, NULL);
	else if (key == DETACH)
		status = pthread_detach(*thread);
	thread_sem_error(status, key);
}

// void ft_sem(sem_t *sem, char *name, t_flag key)
// {
// 	int status;
// 	if (key == OPEN)
// 		status = sem_open(name, O_CREAT, 0644, 0);
// 	if (key == WAIT)
// 		status = sem_wait(sem);
// 	else if (key == POST)
// 		status = sem_post(sem);
// 	else if (key == CLOSE)
// 		status = sem_close(sem);
// 	else if (key == UNLINK)
// 		status = sem_unlink(name);
// 	else
// 	{
// 		print_error(RED"Wrong key num for semaphores"RESET);
// 		return ;
// 	}
// 	thread_mutex_error(status, key);
// }