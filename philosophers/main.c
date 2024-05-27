/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:50:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/27 18:28:00 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
