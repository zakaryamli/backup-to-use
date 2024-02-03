/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:25:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/03 15:29:28 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void ft_execution(char *cmd, s_pipe *needs)
{
	needs->path = find_path(cmd, needs->env);
	needs->cmd = ft_split(cmd, ' ');
	if(-1 == execve(needs->path, needs->cmd, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}
void	cmd_executer(char *cmd, s_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		error_handler("pipe");
	needs->pid = fork();
	if (needs->pid == -1)
		error_handler("fork");
	if (needs->pid == 0)
	{
		close(needs->fd[0]);
		if(-1 == dup2(needs->fd[1], 1))
			error_handler("dup2");
		close(needs->fd[1]);
		ft_execution(cmd, needs);
	}
	else
	{
		close(needs->fd[1]);
		if( -1 == dup2(needs->fd[0], 0))
			error_handler("dup2");
		close(needs->fd[0]);
	}
}
void ff1()
{
	system("leaks pipex_bonus");
}
void last_child(int ac, char **av, s_pipe needs)
{
	needs.pid = fork();
	if(needs.pid == -1)
		error_handler("fork");
	if(needs.pid == 0)
	{
		if(-1 == dup2(needs.outfile, 1))
			error_handler("dup2");
		close(needs.outfile);
		ft_execution(av[ac - 2], &needs);
	}
	if(needs.infile != -1)
		while(wait(NULL) != -1)
			;
	close(0);
	close(needs.outfile);
}
void first_cmd (int ac, char **av, s_pipe *needs)
{
	if(-1 == dup2(needs->infile, 0))
		error_handler("dup2");
	close(needs->infile);
	while (needs->i < ac - 2)
	{
		cmd_executer(av[needs->i], needs);
		needs->i++;
	}
}
void heredoc_handler(s_pipe *needs)
{
	char *line;
	
	needs->infile = open("tempfile",O_CREAT | O_RDWR, 0777);
	if(needs->infile == -1)
		error_handler("here_doc");
	while(1)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(0);
			if(!line)
				break ;
		if (!ft_strncmp(line,  needs->limiter, ft_strlen(line) - 1))
			break ;
		ft_putstr_fd(line, needs->infile);
		free(line);
	}
	free(line);
	// dprintf(2, "limiter ===%s       line ==== %s    strcmp ===%d \n", needs->limiter, line, ft_strncmp(line,  needs->limiter, ft_strlen(line) - 1));
	close(needs->infile);
	needs->infile = open("tempfile",O_CREAT | O_RDWR);
	if(needs->infile == -1)
		error_handler("here_doc");
}
int main(int ac, char **av, char **env)
{
	atexit(ff1);
	s_pipe needs;
	needs.i = 2;
	needs.step = 0;
	if(!ft_strcmp(av[1], "here_doc"))
	{
		needs.limiter = av[2];
		heredoc_handler(&needs);
		needs.i = 3;
		needs.step = 1;
	}
	else
	{
		needs.infile = open(av[1], O_RDONLY);
		if(needs.infile == -1)
			perror("infile");
	}
	needs.outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if(needs.outfile == -1)
		perror("outfile");
	needs.env = env;
	first_cmd(ac, av, &needs);
	last_child(ac, av, needs);
	// dprintf(1, "awkefug");
	if(needs.step)
		unlink("tempfile");
}
