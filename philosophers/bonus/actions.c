/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:38:43 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/02 18:14:10 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_action(t_action key, t_philo *philo)
{
	// if (philo->full)
	// 	return ;	
	sem_wait(philo->table->write_lock);
	if (key == PICK_L_FORK || (key == PICK_R_FORK))
	{
		philo->fork_time = get_time() - philo->table->action_start;
		printf(GREEN"%zu\t%ld\thas taken a fork\n"RESET, philo->fork_time, philo->count);
	}
	else if (key == EATING)
	{
		philo->last_meal = get_time() - philo->table->action_start;
			printf(GREEN"%zu\t%ld\tis eating\n"RESET,philo->last_meal , philo->count);
	}
	else if (key == SLEEPING)
	{
		philo->last_sleep = get_time() -  philo->table->action_start;
			printf(GREEN"%ld\t%ld\tis sleeping\n"RESET, philo->last_sleep , philo->count);
	}
	else if (key == THINKING)
	{
		philo->last_think = get_time() -  philo->table->action_start;
			printf(GREEN"%zu\t%ld\tis thinking\n"RESET,philo->last_think ,philo->count);
	}
	sem_post(philo->table->write_lock);

}

void thinking(t_philo *philo)
{
	write_action(THINKING, philo);
}
void eating(t_philo *philo)
{
	sem_wait(philo->table->fork_lock);
	write_action(PICK_L_FORK, philo);
	sem_wait(philo->table->fork_lock);
	write_action(PICK_R_FORK, philo);
	philo->last_meal = get_time() - philo->table->action_start;
	write_action(EATING, philo);
	philo->meals++;
	ft_usleep(philo->table->time_to_eat, philo->table);
	sem_post(philo->table->fork_lock);
	sem_post(philo->table->fork_lock);
}
