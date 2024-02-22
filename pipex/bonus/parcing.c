/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:00:59 by zyamli            #+#    #+#             */
/*   Updated: 2024/02/14 13:16:09 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_leaks_arr(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*find_commands(char *av, char **pathes)
{
	char	*result;
	char	**command;
	char	*path;
	int		i;

	command = ft_split(av, ' ');
	if (ft_strchr(av, '/'))
	{
		result = ft_strdup(command[0]);
		return (free_leaks_arr(command), result);
	}
	path = ft_strjoin("/", command[0]);
	free_leaks_arr(command);
	i = 0;
	while (pathes[i])
	{
		result = ft_strjoin(pathes[i], path);
		if (access(result, F_OK) == 0 || access(result, X_OK) == 0)
			return (free(path), result);
		i++;
		free(result);
		result = "\0";
	}
	ft_putstr_fd("command not found\n", 2);
	return (NULL);
}

char	**extract_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH"))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	ft_print_error("PATH not found\n");
	return (NULL);
}

char	*find_path(char *cmd, char *env[])
{
	char	**to_look;
	char	*path;

	to_look = extract_paths(env);
	if (!*to_look)
		ft_print_error("PATH not found\n");
	path = find_commands(cmd, to_look);
	if (!path)
		ft_print_error("command error\n");
	free_leaks_arr(to_look);
	return (path);
}
