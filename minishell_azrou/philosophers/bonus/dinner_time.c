/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:36:32 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 17:06:21 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*dinner_action(t_philo	*philo)
{
	if (philo->count % 2 != 0)
		ft_usleep(philo->table->time_to_eat);
	while (1)
	{
		if (philo->meals == philo->table->meals_limit)
			sem_post(philo->table->full);
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep);
		thinking(philo);
	}
	return (NULL);
}

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		philo->death = get_time()
			- philo->table->action_start - philo->last_meal;
		if (philo->death >= philo->table->time_to_die)
		{
			sem_wait(philo->table->write_lock);
			printf(RED"%zu\t%ld\tdied\n"RESET, philo->death, philo->count);
			sem_post(philo->table->end_simu);
			return (NULL);
		}
	}
	return (NULL);
}

void	process_handler(t_philo *philo)
{
	thread_handler(&philo->thread, check_death, philo, CREATE);
	dinner_action(philo);
	exit(0);
}

void	close_semaphores(t_table *table)
{
	(void)table;
	sem_unlink("/forks_lock");
	sem_close(table->fork_lock);
	sem_unlink("/write_lock");
	sem_close(table->write_lock);
	sem_unlink("/full_check");
	sem_post(table->full);
	sem_close(table->full);
	sem_unlink("/end_check");
	sem_close(table->end_simu);
}

void	dinner_time(t_table *table)
{
	int			i;
	pthread_t	th;

	i = 0;
	if (table->meals_limit == 0)
		return ;
	table->action_start = get_time();
	while (i < table->philos_num)
	{
		table->pid[i] = fork();
		if (table->pid[i] == -1)
			print_error("fork error");
		if (table->pid[i] == 0)
			process_handler(&table->philo[i]);
		i++;
	}
	thread_handler(&th, check_full, table, CREATE);
	pthread_detach(th);
	sem_wait(table->end_simu);
	kill_all(table);
	close_semaphores(table);
}
