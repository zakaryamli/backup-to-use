/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:00:50 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 16:26:37 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <libc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>

#define RESET	"\x1b[0m"
#define BLACK	"\x1b[1;30m"
#define RED		"\x1b[1;31m"
#define GREEN	"\x1b[1;32m"
#define YELLO	"\x1b[1;33m"
#define BLUE	"\x1b[1;34m"
#define MAGENTA	"\x1b[1;35m"
#define CYAN	"\x1b[1;36m"
#define WHITE	"\x1b[1;37m"

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				frk_cnt;
}	t_fork;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	long			philos_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_limit;
	long			action_start;
	bool			action_end;
	bool			start_threads;
	bool			all_in;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	write_lock;
	t_fork			*fork_arr;
	t_philo			*philo;
}	t_table;

struct s_philo
{
	long			l_fork_time;
	long			r_fork_time;
	long			last_sleep;
	long			last_think;
	long			death;
	long			count;
	long			meals;
	bool			full;
	long			last_meal;
	t_fork			*r_fork;
	t_fork			*l_fork;
	pthread_t		thread;
	t_table			*table;
	pthread_mutex_t	philo_lock;
};

typedef enum s_flag
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	JOIN,
	CREATE,
	DETACH,
}	t_flag;

typedef enum s_action
{
	PICK_R_FORK,
	PICK_L_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DIED,
}	t_action;

void print_error(char *err);
int	ft_atoi(const char *str);
void dinner_time(t_table *table);
void thread_handler(pthread_t *thread, void *(*func)(void *), void *data, t_flag key);
void eating(t_philo *philo);
void thinking(t_philo *philo);
void	write_action(t_action key, t_philo *philo);
long	get_val_long(pthread_mutex_t *mtx, long	*to_change);
void	set_val_long(pthread_mutex_t *mtx, long	*to_change, long val);
bool	action_done(t_table *table);
bool	get_val_bool(pthread_mutex_t *mtx, bool	*to_change);
void	set_val_bool(pthread_mutex_t *mtx, bool	*to_change, bool val);
void ft_mutexes(pthread_mutex_t *mutex, t_flag key);
void thread_handler(pthread_t *thread, void *(*func)(void *), void *data, t_flag key);
void fork_handler(t_philo *philo, t_table *table, int pos);
int	parsing(t_table *table, char **av);
void	print_error(char *err);
size_t	get_time(void);
void ft_usleep(int miliseconds, t_table *table);
void	freez_threads(t_philo *philo);
#endif