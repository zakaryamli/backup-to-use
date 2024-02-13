/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:36:01 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/13 17:43:52 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	needs;

	if (!*env || ac < 5)
		error_handler("input error");
	needs.i = 2;
	needs.step = 0;
	needs.link_var = 0;
	if (!ft_strcmp(av[1], "here_doc"))
	{
		needs.limiter = av[2];
		heredoc_handler(&needs);
		needs.i = 3;
		needs.step = 1;
		needs.link_var = 1;
	}
	needs.infile_name = av[1];
	needs.outfile_name = av[ac - 1];
	needs.env = env;
	first_cmd(ac, av, &needs);
	last_child(ac, av, needs);
	ft_unlink(&needs);
}
