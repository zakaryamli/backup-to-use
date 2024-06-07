/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:42:26 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/06 16:44:57 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (val);
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
	return (val);
}
