/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assing_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:57 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/01 16:11:45 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void fork_handler(t_philo *philo, t_table *table, int pos)
// {
// 	philo->r_fork = table->fork_arr + pos;
// 	if (pos == table->philos_num - 1)
// 		philo->l_fork = table->fork_arr;
// 	else
// 		philo->l_fork = table->fork_arr + pos + 1;
// }