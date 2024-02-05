/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:25:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/05 11:38:04 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void open_fds(void)
{
	int i = -1;
	while (++i < FD_SETSIZE)
	{
		if (fcntl(i, F_GETFD) != -1)
			dprintf(2, "fd : %d is open\n", i);
	}
}

void ft_execution(char *cmd, s_pipe *needs)
{
	needs->path = find_path(cmd, needs->env);
	needs->cmd = ft_split(cmd, ' ');
	if(-1 == execve(needs->path, needs->cmd, needs->env))
		(close(0), close(needs->infile), error_handler("execve"));
}
void	open_handler(s_pipe *needs)
{
	if(needs->step == 0)
		{
		dprintf(2, "hello\n");
			needs->infile = open(needs->infile_name, O_RDONLY);
			if(needs->infile == -1)
				(close(needs->fd[0]), close(needs->fd[1]),close(0), error_handler("open"));
			if(-1 == dup2(needs->infile, 0))
		 		error_handler("dup2");
			close(needs->infile);
		}
		if(needs->step == 1)
		{
			if(-1 == dup2(needs->infile, 0))
		 		error_handler("dup2");
			close(needs->infile);
		}
		
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
		open_handler(needs);
		dprintf(2, "child : %d\n", getpid());
		if(-1 == dup2(needs->fd[1], 1))
			error_handler("dup2");
		(close(needs->fd[1]), close(needs->fd[0]));
		ft_execution(cmd, needs);
	}
	else
	{
			needs->step = 2;
		if(-1 == dup2(needs->fd[0], 0))
			error_handler("dup2");
		(close(needs->fd[0]), close(needs->fd[1]));
	}
}

void ff1()
{
	system("lsof -c pipex_bonus");
}

void last_child(int ac, char **av, s_pipe needs)
{
	needs.pid = fork();
	if(needs.pid == -1)
		error_handler("fork");
	if(needs.pid == 0)
	{
		dprintf(2, "child : %d\n", getpid());
		needs.outfile = open(needs.outfile_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if(needs.outfile == -1)
			perror("outfile");
		if(-1 == dup2(needs.outfile, 1))
			error_handler("dup2");
		close(needs.outfile);
		ft_execution(av[ac - 2], &needs);
	}
	// if(needs.infile != -1)
	while(wait(NULL) != -1)
		;
	close(0);
	// close(needs.outfile);
}

void first_cmd (int ac, char **av, s_pipe *needs)
{
	
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
	dprintf(2, "limiter ===%s       line ==== %s    strcmp ===%d \n", needs->limiter, line, ft_strncmp(line,  needs->limiter, ft_strlen(line) - 1));
	free(line);
	close(needs->infile);
	needs->infile = open("tempfile",O_RDWR);
	if(needs->infile == -1)
		error_handler("here_doc");
}
void ft_unlink(s_pipe *needs)
{
	if(needs->link_var == 1)
	{
		if(-1 == unlink("tempfile"))
			(perror("unlink"));
		close(needs->infile);
	}
}
int main(int ac, char **av, char **env)
{
	atexit(ff1);
	s_pipe needs;

	if(!*env || ac < 5)
		error_handler("input error");
	needs.i = 2;
	needs.step = 0;
	needs.link_var = 0;
	dprintf(2, "Le parent : %d\n", getpid());
	if(!ft_strcmp(av[1], "here_doc"))
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
	open_fds();
	// dprintf(1, "awkefug");
	ft_unlink(&needs);
	
}
