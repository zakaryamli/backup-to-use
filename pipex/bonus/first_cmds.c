/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:38:25 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/13 17:44:13 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	open_handler(t_pipe *needs)
{
	if (needs->step == 0)
	{
		needs->infile = open(needs->infile_name, O_RDONLY);
		if (needs->infile == -1)
			(close(needs->fd[0]), close(needs->fd[1]),
				close(0), error_handler("open"));
		if (-1 == dup2(needs->infile, 0))
			error_handler("dup2");
		close(needs->infile);
	}
	if (needs->step == 1)
	{
		if (-1 == dup2(needs->infile, 0))
			error_handler("dup2");
		close(needs->infile);
	}
}

static void	cmd_executer(char *cmd, t_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		error_handler("pipe");
	needs->pid = fork();
	if (needs->pid == -1)
		error_handler("fork");
	if (needs->pid == 0)
	{
		open_handler(needs);
		if (-1 == dup2(needs->fd[1], 1))
			error_handler("dup2");
		(close(needs->fd[1]), close(needs->fd[0]));
		ft_execution(cmd, needs);
	}
	else
	{
		needs->step = 2;
		if (-1 == dup2(needs->fd[0], 0))
			error_handler("dup2");
		(close(needs->fd[0]), close(needs->fd[1]));
	}
}

void	first_cmd(int ac, char **av, t_pipe *needs)
{
	while (needs->i < ac - 2)
	{
		cmd_executer(av[needs->i], needs);
		needs->i++;
	}
}
