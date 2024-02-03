/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:30:40 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/03 13:44:12 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 10
# endif
typedef struct t_pipe
{
	// int *pids;
	int i;
	pid_t pid;
	// int j;
	int fd[2];
	int step;
	int infile;
	int outfile;
	char *infile_name;
	char *outfile_name;
	char *path;
	// char *middle_path;
	// char *second_path;
	char **cmd;
	// char **middle_cmd;
	char *limiter;
	char **env;
}s_pipe;
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
int		ft_strcmp(const char *str1, const char *str2);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_join_it(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif