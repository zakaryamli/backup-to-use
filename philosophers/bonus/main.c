/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:50:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 15:48:14 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void philo_stuff(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philos_num)
	{
		philo = table->philo + i;
		philo->count = i + 1;
		philo->meals = 0;
		philo->table = table;
		philo->last_meal = 0;
		i++;
	}
}

void philo_init(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->philos_num);
	if(!table->philo)
		return (print_error("malloc erorr"));
	sem_unlink("/forks_lock");
	table->fork_lock = sem_open("/forks_lock", O_CREAT, 0777, table->philos_num);
	if (table->fork_lock == SEM_FAILED)
		return(print_error("sem error"));
	sem_unlink("/write_lock");
	table->write_lock = sem_open("/write_lock", O_CREAT, 0777, 1);
	if (table->write_lock == SEM_FAILED)
		return(print_error("sem error"));
	sem_unlink("/full_check");
	table->full = sem_open("/full_check", O_CREAT, 0777, 0);
	if (table->full == SEM_FAILED)
		return(print_error("sem error"));
	sem_unlink("/end_check");
	table->end_simu = sem_open("/end_check", O_CREAT, 0777, 0);
	if (table->end_simu == SEM_FAILED)
		return(print_error("sem error"));
	table->pid = malloc(sizeof(int) * table->philos_num);
	if(!table->pid)
		return (print_error("malloc erorr"));
	philo_stuff(table);

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
