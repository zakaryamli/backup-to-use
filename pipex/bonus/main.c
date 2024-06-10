/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:36:01 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/04 21:26:20 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (1);
}
void ff()
{
	system("leaks pipex_bonus");
}

int	main(int ac, char **av, char **env)
{
	t_pipe	needs;
	// atexit(ff);
	if (!*env || ac < 5)
		ft_print_error("input error");
	needs.i = 2;
	needs.step = 0;
	needs.link_var = 0;
	if (!ft_strcmp(av[1], "here_doc"))
	{
		needs.limiter = ft_strjoin(av[2], "\n");
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
	while (wait(NULL) != -1)
		;
	ft_unlink(&needs);
	while(1);
}
