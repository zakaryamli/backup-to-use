/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:56:08 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/14 15:11:57 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	first_child_routine(t_pipe *needs)
{
	int	e;

	needs->infile = open(needs->infile_name, O_RDONLY);
	if (needs->infile == -1)
		(close(needs->fd[0]), close(needs->fd[1]), error_handler("open error"));
	e = dup2(needs->infile, STDIN_FILENO);
	if (e == -1)
		error_handler("dup2 error");
	e = dup2(needs->fd[1], STDOUT_FILENO);
	if (e == -1)
		error_handler("dup2 error");
	(close(needs->fd[1]), close(needs->fd[0]), close(needs->infile));
	e = execve(needs->first_path, needs->first_cmd, needs->env);
	if (e == -1)
		error_handler("dup2 error");
}

void	second_child_routine(t_pipe *needs)
{
	int	e;

	needs->outfile = open(needs->outfile_name, O_TRUNC | O_CREAT
			| O_RDWR, 0000644);
	if (needs->outfile == -1)
		error_handler("dup2 error");
	e = dup2(needs->fd[0], STDIN_FILENO);
	if (e == -1)
		error_handler("dup2 error");
	e = dup2(needs->outfile, STDOUT_FILENO);
	if (e == -1)
		error_handler("dup2 error");
	(close(needs->fd[0]), close(needs->outfile), close(needs->fd[1]));
	e = execve(needs->second_path, needs->second_cmd, needs->env);
	if (e == -1)
		error_handler("dup2 error");
}

void	pipex(t_pipe *needs)
{
	int	p;

	p = pipe(needs->fd);
	if (p < 0)
		error_handler("pipe error");
	needs->pid1 = fork();
	if (needs->pid1 == -1)
		error_handler("fork error");
	if (needs->pid1 == 0)
		first_child_routine(needs);
	else
	{
		needs->pid2 = fork();
		if (needs->pid2 == -1)
			error_handler("fork error");
	}
	if (needs->pid2 == 0)
		second_child_routine(needs);
	(close(needs->fd[0]), close(needs->fd[1]));
	wait(NULL);
	wait(NULL);
}

t_pipe	set_values(char **av, char **env)
{
	t_pipe	needs;

	needs.first_path = find_path(av[2], env);
	if (!needs.first_path)
		error_handler("PATH ERROR");
	needs.second_path = find_path(av[3], env);
	if (!needs.second_path)
		error_handler("PATH ERROR");
	needs.first_cmd = ft_split(av[2], ' ');
	if (!needs.first_cmd)
		perror("wrong first command");
	needs.second_cmd = ft_split(av[3], ' ');
	if (!needs.second_cmd)
		perror("wrong first command");
	needs.env = env;
	needs.infile_name = av[1];
	needs.outfile_name = av[4];
	return (needs);
}
