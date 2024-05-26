/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:50:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/25 22:45:25 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *err)
{
	while(*err)
		write(2, err++, 1);
}


static	int	invalid_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0' || !str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_handler(const char *str)
{
	int			i;
	int			sign;
	long long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = tmp * 10 + (str[i] - 48);
		if (tmp > 2147483647 && sign == 1)
			return (1);
		if (tmp > 2147483648 && sign == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	check_ifvalid(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_handler(arg[i]) || invalid_str(arg[i]))
		{
			print_error(RED"Invalid Input");
			return (1);
		}
		i++;
	}
	return (0);
}
int	parsing(t_table *table, char **av)
{
	if(check_ifvalid(&av[1]))
		return (1);
	table->philos_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1e3;
	table->time_to_eat = ft_atoi(av[3]) * 1e3;
	table->time_to_sleep = ft_atoi(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		{
			print_error(RED"Timestamps less than 60ms"RESET);
			return (1);
		}
	if (av[5])
		table->meals_limit = ft_atoi(av[5]);
	else
		table->meals_limit = -1;
	return (0);
}
static void mutex_error(int status, t_flag key)
{
	if (status != 0)
	{
		if (key == LOCK)
			print_error(RED"mutex lock error"RESET);
		if (key == UNLOCK)
			print_error(RED"mutex unlock error"RESET);
		if (key == INIT)
			print_error(RED"mutex init error"RESET);
		if (key == DESTROY)
			print_error(RED"mutex destroy error"RESET);
	}
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
	mutex_error(status, key);
}

void fork_handler(t_philo *philo, t_fork *forks, int pos)
{
	philo->l_fork = &forks[(pos + 1) % philo->table->philos_num];
	philo->r_fork = &forks[pos];
	if ((philo->count % 2) == 0)
	{
		philo->r_fork = &forks[pos];
		philo->l_fork = &forks[(pos + 1) % philo->table->philos_num];	
	}
}

void philo_init(t_table *table)
{
	int i;
	t_philo *philo;
	i = 0;
	table->action_end = false;
	table->philo = malloc(sizeof(t_philo) * table->philos_num);
	//protect malloc
	table->fork_arr = malloc(sizeof(t_fork) * table->philos_num);
	//protect malloc
	while(i < table->philos_num)
	{
		ft_mutexes(&table->fork_arr[i].fork, INIT);
		table->fork_arr[i].frk_cnt = i;
		i++;
	}
	i = 0;
	while (i < table->philos_num)
	{
		philo = table->philo + i;
		philo->count = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		i++;
	}
}

void thread_handler()
{
	
}

void dinner_action(t_table *table)
{
	int i;

	i = 0;
	if (table->meals_limit == 0)
		return ;
	else if (table->philos_num == 1)
		;
	else
	{
		while(i < table->philo)
		{
			thread_handler()
		}
		
	}
}

int	main (int ac, char **av)
{
	t_table	table;
	if (ac == 5 || ac == 6)
	{
		if (parsing(&table, av))
			return (1);
		philo_init(&table);
	}
	else
	{
		print_error(RED"Wrong Input"RESET);
		return (1);
	}
}
