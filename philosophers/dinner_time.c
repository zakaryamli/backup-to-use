/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:36:32 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/27 21:51:56 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freez_threads(t_philo *philo)
{
	bool 	i;

	i = false;
	while(1)
	{
		ft_mutexes(&philo->table->table_lock, LOCK);
		i = philo->table->all_in;
		ft_mutexes(&philo->table->table_lock, UNLOCK);
		
		if (i == true)
			break ;
	}
	if(philo->count % 2 != 0)
		ft_usleep(philo->table->time_to_eat, philo->table);
	
}

void	*dinner_action(void *ptr)
{
	t_philo	*philo;
	philo = (t_philo *)ptr;
	freez_threads(philo);
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

int	death(t_philo *philo)
{
	size_t var;
	ft_mutexes(&philo->philo_lock, LOCK);
	var = get_time() - philo->table->action_start - philo->last_meal;
	printf("%ld    %ld   %zu\n", philo->last_meal, philo->table->action_start, var);
	ft_mutexes(&philo->philo_lock, UNLOCK);
	if(var > philo->table->time_to_die)
		return (1);
	return(0);
}

void check_death(t_table *table)
{
	int i;

	while(1)
	{
		i = 0;
		while (i < table->philos_num)
		{
			if(death(&table->philo[i]))
			{
				ft_mutexes(&table->write_lock, LOCK);
				set_val_bool(&table->table_lock, &table->action_end, true);
				// ft_mutexes(&table->table_lock, LOCK);
				table->philo->death = get_time() -  table->action_start;
				printf(RED"%zu\t%ld\tdied\n"RESET,table->philo->death ,table->philo->count);
				ft_mutexes(&table->write_lock, UNLOCK);
				
				return ;
			}
			i++;
		}	
	}
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
		table->all_in = false;
		while(i < table->philos_num)
		{
			thread_handler(&table->philo[i].thread, dinner_action, &table->philo[i], CREATE);
			i++;
		}
		table->action_start = get_time();
		ft_mutexes(&table->table_lock, LOCK);
		table->all_in = true;
		ft_mutexes(&table->table_lock, UNLOCK);
		set_val_bool(&table->table_lock, &table->start_threads, true);
		check_death(table);
	}
	i = 0;
	while (i < table->philos_num)
	{
		thread_handler(&table->philo[i].thread, NULL, NULL, JOIN);
		i++;
	}
}