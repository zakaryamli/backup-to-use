/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:25:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/13 17:43:42 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execution(char *cmd, t_pipe *needs)
{
	needs->path = find_path(cmd, needs->env);
	if (!needs->path)
		error_handler("error PATH");
	needs->cmd = ft_split(cmd, ' ');
	if (-1 == execve(needs->path, needs->cmd, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}

void	last_child(int ac, char **av, t_pipe needs)
{
	needs.pid = fork();
	if (needs.pid == -1)
		error_handler("fork");
	if (needs.pid == 0)
	{
		needs.outfile = open(needs.outfile_name, O_RDWR
				| O_CREAT | O_TRUNC, 0777);
		if (needs.outfile == -1)
			perror("outfile");
		if (-1 == dup2(needs.outfile, 1))
			error_handler("dup2");
		close(needs.outfile);
		ft_execution(av[ac - 2], &needs);
	}
	while (wait(NULL) != -1)
		;
	close(0);
}

void	heredoc_handler(t_pipe *needs)
{
	char	*line;

	needs->infile = open("tempfile", O_CREAT | O_RDWR, 0777);
	if (needs->infile == -1)
		error_handler("here_doc");
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, needs->limiter, ft_strlen(line) - 1))
			break ;
		ft_putstr_fd(line, needs->infile);
		free(line);
	}
	free(line);
	close(needs->infile);
	needs->infile = open("tempfile", O_RDWR);
	if (needs->infile == -1)
		error_handler("here_doc");
}

void	ft_unlink(t_pipe *needs)
{
	if (needs->link_var == 1)
	{
		if (-1 == unlink("tempfile"))
			(perror("unlink"));
		close(needs->infile);
	}
}
