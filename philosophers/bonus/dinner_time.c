/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:36:32 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/03 16:44:40 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	freez_process(t_philo *philo)
{
	
	if(philo->count % 2 != 0)
		ft_usleep(philo->table->time_to_eat, philo->table);

	
}

void	*dinner_action(t_philo	*philo)
{
	freez_process(philo);
	while(1)
	{		
		if (philo->meals == philo->table->meals_limit)
			sem_post(philo->table->full);
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void  *check_death(void *data)
{
	int i;
	t_philo *philo;
	philo = (t_philo *)data;
	while(1)
	{
		// printf(">> start %ld\n", philo->table->action_start);
		philo->death = get_time() - philo->table->action_start - philo->last_meal;
		if(philo->death >= philo->table->time_to_die)
		{
			sem_wait(philo->table->write_lock);
			printf(RED"%zu\t%ld\tdied\n"RESET, philo->death, philo->count);
			sem_post(philo->table->end_simu);
			return(NULL);
		}
			
 	}	
	
	return(NULL);
}

void process_handler(t_philo *philo, int i)
{
		thread_handler(&philo->thread, check_death, philo, CREATE);
		dinner_action(philo);
		exit(0);
}

void kill_all(t_table *table)
{
	int i;

	i = 0;
	while(i < table->philos_num)
	{
		kill(table->pid[i], SIGKILL);
		i++;
	}
}

void *check_full(void *data)
{
	t_table *table;
	int i;
	table = (t_table *)data;
	i = 0;
	while(i < table->philos_num)
	{
		sem_wait(table->full);
		i++;
	}
	sem_post(table->end_simu);
	return(NULL);
} 
void dinner_time(t_table *table)
{
	int i;
	pthread_t th;

	i = 0;
	if (table->meals_limit == 0)
		return ;
	// else if (table->philos_num == 1)
	// 	;
	else
	{
		table->action_start = get_time();
		// printf(">> start %ld\n", table->action_start);
		while(i < table->philos_num)
		{
			table->pid[i] = fork();
			if(table->pid[i] == -1)
				print_error("fork error");
			if(table->pid[i] == 0)
				process_handler(&table->philo[i], i);
			
			i++;
		}
	}
	
	thread_handler(&th, check_full, table, CREATE);
	pthread_detach(th);
	// i = 0;
	// while (i < table->philos_num)
	// {
	// 	thread_handler(&table->philo[i].thread, NULL, NULL, JOIN);
	// 	i++;
	// }
	sem_wait(table->end_simu);
	kill_all(table);

	// distroy mutexes
}
