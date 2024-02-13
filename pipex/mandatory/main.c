/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:09:16 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/13 16:25:00 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	needs;

	if (ac < 5)
		error_handler("input error");
	if (!*env)
		error_handler("environnement error");
	needs = set_values(av, env);
	pipex(&needs);
	free(needs.first_path);
	free(needs.second_path);
	free_leaks_arr(needs.first_cmd);
	free_leaks_arr(needs.second_cmd);
}
