/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:38:43 by zyamli            #+#    #+#             */
/*   Updated: 2024/05/28 13:57:59 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(t_action key, t_philo *philo)
{
	if (philo->full)
		return ;
	ft_mutexes(&philo->table->write_lock, LOCK);
	if (key == PICK_L_FORK || (key == PICK_R_FORK && !action_done(philo->table)))
	{
		if(key == PICK_L_FORK && !action_done(philo->table))
		{
			philo->l_fork_time = get_time() - philo->table->action_start;
			printf(GREEN"%zu\t%ld\thas taken a fork\n"RESET, philo->l_fork_time, philo->count);
		}
		if(key == PICK_R_FORK && !action_done(philo->table))
		{
			philo->r_fork_time = get_time() - philo->table->action_start;
			printf(GREEN"%zu\t%ld\thas taken a fork\n"RESET, philo->r_fork_time, philo->count);
		}
	}
	else if (key == EATING && !action_done(philo->table))
	{
		ft_mutexes(&philo->philo_lock, LOCK);
		philo->last_meal = get_time() - philo->table->action_start;
		if (!action_done(philo->table))
			printf(GREEN"%zu\t%ld\tis eating\n"RESET,philo->last_meal , philo->count);
		ft_mutexes(&philo->philo_lock, UNLOCK);
	}
	else if (key == SLEEPING && !action_done(philo->table))
	{
		philo->last_sleep = get_time() -  philo->table->action_start;
		if (!action_done(philo->table))
			printf(GREEN"%ld\t%ld\tis sleeping\n"RESET, philo->last_sleep , philo->count);
	}
	else if (key == THINKING && !action_done(philo->table))
	{
		philo->last_think = get_time() -  philo->table->action_start;
		if (!action_done(philo->table))
			printf(GREEN"%zu\t%ld\tis thinking\n"RESET,philo->last_think ,philo->count);
	}
	// else if (key == DIED && !action_done(philo->table))
	// {
	// 	philo->death = get_time() -  philo->table->action_start;
	// 	if (!action_done(philo->table))
	// 		printf(RED"%zu\t%ld\tdied\n"RESET,philo->death ,philo->count);
	// }
	ft_mutexes(&philo->table->write_lock, UNLOCK);

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
	if (philo->table->meals_limit > 0 && philo->meals > philo->table->meals_limit)
		set_val_bool(&philo->philo_lock, &philo->full, true);
	ft_mutexes(&philo->l_fork->fork, UNLOCK);
	ft_mutexes(&philo->r_fork->fork, UNLOCK);
}