/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:50:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/27 15:18:31 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL))
		print_error(RED"gettimeofday error"RESET);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void ft_usleep(int miliseconds, t_table *table)
{
	int start;

	start = get_time();
	while(start - get_time() < miliseconds)
		usleep(1);
}

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
void ft_mutexes(pthread_mutex_t *mutex, t_flag key)
{
	int status;
	if (key == LOCK)
	{
		status = pthread_mutex_lock(mutex);
	}
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
void fork_handler(t_philo *philo, t_table *table, int pos)
{
	// philo->l_fork = &forks[(pos + 1) % philo->table->philos_num];
	// philo->r_fork = &forks[pos];
	// if ((philo->count % 2) == 0)
	// {
	// 	philo->r_fork = &forks[pos];
	// 	philo->l_fork = &forks[(pos + 1) % philo->table->philos_num];
	// }
	philo->r_fork = table->fork_arr + pos;
	if (pos == table->philos_num - 1)
		philo->l_fork = table->fork_arr;
	else
		philo->l_fork = table->fork_arr + pos + 1;
}

void	set_val_bool(pthread_mutex_t *mtx, bool	*to_change, bool val)
{
	ft_mutexes(mtx, LOCK);
	*to_change = val;
	ft_mutexes(mtx, UNLOCK);
}
bool	get_val_bool(pthread_mutex_t *mtx, bool	*to_change)
{
	bool	val;
	
	ft_mutexes(mtx, LOCK);
	val = *to_change;
	ft_mutexes(mtx, UNLOCK);
	return(val);
}

bool	action_done(t_table *table)
{
	return (get_val_bool(&table->table_lock, &table->action_end));
}

void	set_val_long(pthread_mutex_t *mtx, long	*to_change, long val)
{
	ft_mutexes(mtx, LOCK);
	*to_change = val;
	ft_mutexes(mtx, UNLOCK);
}

long	get_val_long(pthread_mutex_t *mtx, long	*to_change)
{
	long	val;
	
	ft_mutexes(mtx, LOCK);
	val = *to_change;
	ft_mutexes(mtx, UNLOCK);
	return(val);
}

void	freez_threads(t_table *table)
{
	if(table->philo->count % 2)
		ft_usleep(table->time_to_eat, table);
}
void	write_action(t_action key, t_philo *philo)
{
	if (philo->full)
		return ;
	ft_mutexes(&philo->table->write_lock, LOCK);
	if (key == PICK_L_FORK || key == PICK_R_FORK && !action_done(philo->table))
		printf(GREEN"%d-> has taken a fork\n"RESET, philo->count);
	else if (key == EATING && !action_done(philo->table))
		printf(GREEN"%d-> is eating\n"RESET, philo->count);
	else if (key == SLEEPING && !action_done(philo->table))
		printf(GREEN"%d-> is sleeping\n"RESET, philo->count);
	else if (key == THINKING && !action_done(philo->table))
		printf(GREEN"%d-> is thinking\n"RESET, philo->count);
	else if (key == DIED && !action_done(philo->table))
		printf(RED"%d-> died\n"RESET, philo->count);
	ft_mutexes(&philo->table->write_lock, UNLOCK);

}
void philo_init(t_table *table)
{
	int i;
	t_philo *philo;
	table->action_end = false;
	table->start_threads = false;
	table->philo = malloc(sizeof(t_philo) * table->philos_num);
	//protect malloc
	ft_mutexes(&table->table_lock, INIT);
	ft_mutexes(&table->write_lock, INIT);
	table->fork_arr = malloc(sizeof(t_fork) * table->philos_num);
	//protect malloc
	i = 0;
	while(i < table->philos_num)
	{
		ft_mutexes(&table->fork_arr[i].fork, INIT);
		table->fork_arr[i].frk_cnt = i;
		i++;
	}
	// norm from here
	i = 0;
	while (i < table->philos_num)
	{
		philo = table->philo + i;
		philo->count = i + 1;
		philo->full = false;
		philo->meals = 0;
		ft_mutexes(&philo->philo_lock, INIT);
		fork_handler(philo, table, i);
		philo->table = table;
		i++;
	}
}
void thinking(t_philo *philo)
{
	write_action(THINKING, philo);
}
void eating(t_philo *philo)
{
	ft_mutexes(&philo->l_fork->fork, LOCK);
	write_action(PICK_L_FORK, philo);
	ft_mutexes(&philo->r_fork->fork, LOCK);
	write_action(PICK_R_FORK, philo);
	set_val_long(&philo->philo_lock, &philo->last_meal, get_time());
	write_action(EATING, philo);
	philo->meals++;
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_limit > 0 && philo->meals == philo->table->meals_limit)
		set_val_bool(&philo->philo_lock, &philo->full, true);
	ft_mutexes(&philo->l_fork->fork, UNLOCK);
	ft_mutexes(&philo->r_fork->fork, UNLOCK);
}

void	*dinner_action(void *ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	freez_threads(philo->table);
	while(!action_done(philo->table))
	{
		if (philo->full)
			break ;
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
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
	thread_mutex_error(status, key);
}

void dinner_time(t_table *table)
{
	int i;

	i = 0;
	if (table->meals_limit == 0)
		return ;
	else if (table->philos_num == 1)
		;
	else
	{
		while(i < table->philos_num)
		{
			thread_handler(&table->philo[i].thread, dinner_action, &table->philo[i], CREATE);
			i++;
		}
		set_val_bool(&table->table_lock, &table->start_threads, true);
	}
	i = 0;
	while (i < table->philos_num)
	{
		thread_handler(&table->philo[i].thread, NULL, NULL, JOIN);
		i++;
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
		dinner_time(&table);
	}
	else
	{
		print_error(RED"Wrong Input"RESET);
		return (1);
	}
}
