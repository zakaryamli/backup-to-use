/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:30:40 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/14 15:12:47 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct t_pipe
{
	pid_t	pid1;
	pid_t	pid2;
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

char	*ft_strstr(const char *haystack, const char *needle);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*find_path(char *av, char *env[]);
int		ft_strchr(const char *s, int c);
char	**check_command(char *av);
void	free_leaks_arr(char **strs);
t_pipe	set_values(char **av, char **env);
void	error_handler(char *str);
void	pipex(t_pipe *needs);
void	ft_putstr_fd(char *s, int fd);
void	ft_print_error(char *str);
#endif