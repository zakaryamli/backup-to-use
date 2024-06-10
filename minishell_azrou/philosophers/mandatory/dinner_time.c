/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:36:32 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 16:40:59 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_action(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	freez_threads(philo);
	while (!action_done(philo->table))
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

int	death(t_philo *philo)
{
	long	var;

	ft_mutexes(&philo->philo_lock, LOCK);
	var = get_time() - philo->table->action_start - philo->last_meal;
	ft_mutexes(&philo->philo_lock, UNLOCK);
	if (var >= philo->table->time_to_die)
		return (1);
	return (0);
}

void	check_death(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->philos_num)
		{
			if (death(&table->philo[i]))
			{
				ft_mutexes(&table->write_lock, LOCK);
				set_val_bool(&table->table_lock, &table->action_end, true);
				table->philo->death = get_time() - table->action_start;
				if (table->philo[i].full != true)
					printf(RED"%zu\t%ld\tdied\n"RESET,
						table->philo->death, table->philo->count);
				ft_mutexes(&table->write_lock, UNLOCK);
				if (table->philos_num == 1)
					ft_mutexes(&table->philo->r_fork->fork, UNLOCK);
				return ;
			}
			i++;
		}
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	ft_mutexes(&table->table_lock, DESTROY);
	ft_mutexes(&table->write_lock, DESTROY);
	while (i < table->philos_num)
	{
		ft_mutexes(&table->fork_arr[i].fork, DESTROY);
		ft_mutexes(&table->philo[i].philo_lock, DESTROY);
		i++;
	}
}

void	dinner_time(t_table *table)
{
	int	i;

	i = 0;
	if (table->meals_limit == 0)
		return ;
	table->all_in = false;
	while (i < table->philos_num)
	{
		thread_handler(&table->philo[i].thread, dinner_action,
			&table->philo[i], CREATE);
		i++;
	}
	table->action_start = get_time();
	ft_mutexes(&table->table_lock, LOCK);
	table->all_in = true;
	ft_mutexes(&table->table_lock, UNLOCK);
	set_val_bool(&table->table_lock, &table->start_threads, true);
	check_death(table);
	i = 0;
	while (i < table->philos_num)
	{
		thread_handler(&table->philo[i].thread, NULL, NULL, JOIN);
		i++;
	}
	destroy_mutex(table);
}
