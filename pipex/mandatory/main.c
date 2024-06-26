/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:09:16 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/14 15:10:10 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	needs;

	if (ac < 5)
		ft_print_error("input error");
	if (!*env)
		ft_print_error("environnement error");
	needs = set_values(av, env);
	pipex(&needs);
	free(needs.first_path);
	free(needs.second_path);
	free_leaks_arr(needs.first_cmd);
	free_leaks_arr(needs.second_cmd);
}
