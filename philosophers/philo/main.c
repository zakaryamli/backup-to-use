/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:50:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/10 19:39:31 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_stuff(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philos_num)
	{
		philo = table->philo + i;
		philo->count = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->last_meal = 0;
		ft_mutexes(&philo->philo_lock, INIT);
		fork_handler(philo, table, i);
		philo->table = table;
		i++;
	}
}

void	philo_init(t_table *table)
{
	int		i;

	table->action_end = false;
	table->start_threads = false;
	table->philo = zyalloc(sizeof(t_philo) * table->philos_num, 'a');
	if (!table->philo)
		return (print_error("malloc erorr"));
	ft_mutexes(&table->table_lock, INIT);
	ft_mutexes(&table->write_lock, INIT);
	table->fork_arr = zyalloc(sizeof(t_fork) * table->philos_num, 'a');
	if (!table->fork_arr)
		return (print_error("malloc erorr"));
	i = 0;
	while (i < table->philos_num)
	{
		ft_mutexes(&table->fork_arr[i].fork, INIT);
		table->fork_arr[i].frk_cnt = i;
		i++;
	}
	philo_stuff(table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&table, av))
			return (1);
		philo_init(&table);
		dinner_time(&table);
		zyalloc(0, 'f');
	}
	else
	{
		print_error(RED"Wrong Input"RESET);
		return (1);
	}
}
