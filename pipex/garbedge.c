/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:52:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/14 14:52:08 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include<unistd.h>
#include<fcntl.h>
typedef struct t_pipe
{
	pid_t	pid;
	int		i;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*infile_name;
	char	*outfile_name;
	char	*first_path;
	char	*second_path;
	char	**first_cmd;
	char	**second_cmd;
	char	**env;
}	t_pipe;

 void ft_execution(char *cmd, t_pipe *needs)
{
	needs->first_path = find_path(cmd, needs->env);
	needs->first_cmd = ft_split(cmd, ' ');
	execve(needs->first_path, needs->first_cmd, needs->env);
}
void	cmd_executer(char *cmd, t_pipe *needs)
{
	if (pipe(needs->fd) == -1)
		exit(0);
	needs->pid = fork();
	if (needs->pid == -1)
		exit(0);
	if (needs->pid == 0)
	{
		close(needs->fd[0]);
		dup2(needs->fd[1], 1);
		if(close(needs->fd[1]) == -1)
			perror("");
		ft_execution(cmd, needs);
	}
	else
	{
		close(needs->fd[1]);
		dup2(needs->fd[0], 0);
		close(needs->fd[0]);
	}
}
// void ff1()
// {
// 	system("lsof -c a.out");
// }
int main(int ac, char **av, char **env)	
{
	// atexit(ff1);
	t_pipe needs;
	needs.infile = open(av[1], O_RDONLY);
	needs.outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	needs.env = env;
	needs.i = 2;
	dup2(needs.infile, 0);
	while (needs.i < ac - 2)
	{
		cmd_executer(av[needs.i], &needs);
		needs.i++;
	}
	dup2(needs.outfile, 1);
	close(needs.outfile);
	ft_execution(av[ac - 2], &needs);
	// exit(0);
}
